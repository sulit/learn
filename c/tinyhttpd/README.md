> ============================================
>   Copyright (C) 2015 All rights reserved.
>
>   filename : README.md
>
>   author : sulit - sulitsrc@163.com
>
>   last modified : 2015-05-24 21:54
>
>   description :
>
> ============================================

tinyhttpd介绍
======

#### 介绍

tinyhttpd 微型服务器，适合于研究http服务器的原理，不能用作成熟产品

#### 分析

* main函数

```
int main(void)
{
	int server_sock = -1;
	u_short port = 0;
	int client_sock = -1;
	struct sockaddr_in client_name;
	int client_name_len = sizeof(client_name);
	pthread_t newthread;

	server_sock = startup(&port);
	printf("httpd running on port %d\n", port);

	while (1) {
		client_sock = accept(server_sock,
				     (struct sockaddr *) &client_name,
				     &client_name_len);
		if (client_sock == -1)
			error_die("accept");
		/* accept_request(client_sock); */
		if (pthread_create
		    (&newthread, NULL, accept_request, client_sock) != 0)
			perror("pthread_create");
	}

	close(server_sock);

	return (0);
}
```

```
int server_sock = -1;
```

定义并初始化了一个服务器端的网络套接字描述符，类似于文件描述符，初始化为-1，而
-1正好是socket建立失败时返回的值，代表无效socket描述符。这样可以防止在socket描
述符未成功得到分配时，被使用。

```
u_short port = 0;
```

端口号初始化为0，是无符号short类型，16位，正好跟端口号0-65535相对。

```
int client_sock = -1;
```

定义并初始化了一个客户端的网络套接字描述符，其他同`server_socket`

```
struct sockaddr_in client_name;
```

sockaddr结构的一些信息，主要是作为其他socket函数的参数

```
int client_name_len = sizeof(client_name);
```

sockaddr_in的结构体大小

```
	pthread_t newthread;
```

新建线程的线程ID

```
server_sock = startup(&port);
printf("httpd running on port %d\n", port);
```

建立socket，并且bind，listen，然后打印绑定的端口号

```
while (1) {
	client_sock = accept(server_sock,
			     (struct sockaddr *) &client_name,
			     &client_name_len);
	if (client_sock == -1)
		error_die("accept");
	/* accept_request(client_sock); */
	if (pthread_create
	    (&newthread, NULL, accept_request, client_sock) != 0)
		perror("pthread_create");
}
```

接受客户端连接，并且创建线程去处理它

```
close(server_sock);
```

关闭服务端套接字

```
	return (0);
```

返回退出服务器

* startup函数

```
int startup(u_short * port)
{
	int httpd = 0;
	struct sockaddr_in name;

	httpd = socket(PF_INET, SOCK_STREAM, 0);
	if (httpd == -1)
		error_die("socket");
	memset(&name, 0, sizeof(name));
	name.sin_family = AF_INET;
	name.sin_port = htons(*port);
	name.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(httpd, (struct sockaddr *) &name, sizeof(name)) < 0)
		error_die("bind");
	if (*port == 0) {	/* if dynamically allocating a port */
		int namelen = sizeof(name);
		if (getsockname(httpd, (struct sockaddr *) &name, &namelen)
		    == -1)
			error_die("getsockname");
		*port = ntohs(name.sin_port);
	}
	if (listen(httpd, 5) < 0)
		error_die("listen");
	return (httpd);
}
```

```
int httpd = 0;
```

服务器端套接字描述符

```
struct sockaddr_in name;
```

sockaddr结构体，下面将被bind函数使用

```
httpd = socket(PF_INET, SOCK_STREAM, 0);
if (httpd == -1)
	error_die("socket");
```

创建socket，并且检验socket是否有效

```
memset(&name, 0, sizeof(name));
name.sin_family = AF_INET;
name.sin_port = htons(*port);
name.sin_addr.s_addr = htonl(INADDR_ANY);
```

设置sockaddr结构体变量，`name.sin_family = AF_INET;`配置协议族，在socket编程中
只能是AF_INET；`name.sin_port = htons(*port);`配置端口号，注意htons函数，这里
的意思是把*port(u_short类型)从主机字节序转化成网络字节序；
`name.sin_addr.s_addr = htonl(INADDR_ANY);`配置网络地址，注意htonl，类似于
hotns，宏INADDR_ANY，是指0.0.0.0，也就是任意地址。

```
	if (bind(httpd, (struct sockaddr *) &name, sizeof(name)) < 0)
		error_die("bind");
```

绑定服务器端套接字和sockaddr结构体的关系。

```
if (*port == 0) {	/* if dynamically allocating a port */
	int namelen = sizeof(name);
	if (getsockname(httpd, (struct sockaddr *) &name, &namelen)
	    == -1)
		error_die("getsockname");
	*port = ntohs(name.sin_port);
}
```

如果port默认为0，系统将从socket中取得相关的端口信息。

```
if (listen(httpd, 5) < 0)
	error_die("listen");
```

监听套接字，并检验执行结果。

```
return (httpd);
```

返回服务器端套接字接口
