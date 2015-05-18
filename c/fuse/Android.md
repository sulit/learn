# Anroid.mk 的编写规则

## 说明

这部分描述了Android.mk构建文件的语法，这个文件描述Android NDK如何执行你的C/C++文件。

## 概览

Android.mk为构建系统描述了你的源码。更明确的有：

 * 这个文件其实是一个构建系统语法一次或多次的微小的GNU Makefile。因此，你应该努力最小化你在这儿声明的变量。也不必要呈现在语法中未定义的任何东西。

 * 这个文件的语法是被设计允许你组织你的源码到模块中，一个模块是下面中的一个：

   1.一个静态库

   2.一个动态库

   3.一个单独可执行的程序

构建系统只安装/拷贝动态库到你的安装包。另外，静态库可以生成动态库。

在一个Android.mk中你可以定一个或多个模块，你可以用相同的源代码文件在多个模块中。

 * 构建系统将为你做很多细节工作。比如，你不需要在Android.mk中列出头文件或者在生成文件之间明确的依赖。NDK构建系统将自动为你处理这些。

这也意味着，当更新NDK到新的版本时，你将在不更改Android.mk文件的同时，从新的工具链/平台中获益。

  * 注意:语法非常接近于在所有android开源工程中被用的Android.mk的语法。在用它们构建系统接口时是不同的，他们的相似性是一种故意的设计，旨在使应用开发者在重用扩展库时更加容易。

## 简单例子

在详细描述语法之前，考虑在Hello-jni简单例子中用到的Android.mk是有好处的。

jni/Android.mk文件描述了用NDK构建系统制作动态库的过程。文件内容如下

	LOCAL_PATH := $(call my-dir)

	include $(CLEAR_VARS)

	LOCAL_MODULE    := hello-jni
	LOCAL_SRC_FILES := hello-jni.c

	include $(BUILD_SHARED_LIBRARY)

下面我们解释一下这些行：

	LOCAL_PATH := $(call my-dir)

一个Android.mk文件必须以LOCAL_PATH变量的定义开始。它是被用来指出在开发树中，源文件的位置。在这个例子中，'my-dir'是由构建系统提供的，被用来返回当前目录的路径（这个目录是包含Android.mk文件自己的目录）。

	include $(CLEAR_VARS)

CLEAR_VARS变量是由构建系统提供的，指向一个特殊的GNU Makefile，这个Makefile将为你清除很多LOCAL_XXX变量（比如LOCAL_MODULE，LOCAL_SRC_FILES，LOCAL_STATIC_LIBRARY）除了LOCAL_PATH。这是必要的，因为所有构建控制文件是被单个GNU Make执行上下文解析的，在这种情况下，所有变量是全局的。

	LOCAL_MODULE    := hello-jni

LOCAL_MODULE这个变量必须被定义，为了唯一确认在你Android.mk文件中描述的每个模块。这个名字必须是唯一的，并且不能包含任何空格。注意构建系统将自动为生成文件添加合适的前缀和后缀，换句话说，一个命名为foo的动态库将生成libfoo.so。

  * 特别注意：如果你命名模块名为libfoo，构建系统将不会添加额外的前缀lib，将生成一样的libfoo.so。这是被从Android平台源码生成的Android.mk文件支持的，你将需要用到这些。

	LOCAL_SRC_FILES := hello-jni.c

LOCAL_SRC_FILES变量必须包含一个C/C++列表，这些文件将被构建和组装进一个模块。注意你将不能列出头文件和已经包含的文件，因为构建系统将自动为你处理这些依赖；只需要列出那些将直接通过编译的源文件，你将觉得这样很好。

  * 注意：C++源文件的默认后缀是.cpp。然而它可以通过定义变量LOCAL_CPP_EXTENSION来指定不同的后缀名。不要忘了.（比如，.cxx将工作，而cxx将不工作）

	include $(BUILD_SHARED_LIBRARY)

BUILD_SHARED_LIBRARY是由构建系统提供的一个变量，这个变量指向一个GNU Makefile脚本，这个脚本负责搜集从最近的一个include开始你定义在LOCAL_XXX中的所有信息，然后决定构建什么，如何正确的做它。BUILD_STATIC_LIBRARY将生成一个静态库。

更多的复杂的例子在samples目录下，你可以看Android.mk的注释。

## 参考

下面是你在Android.mk中或者依赖，或者定义的变量的列表。你可以定义你自己用的其他的变量，但是NDK构建系统保留下列变量名：

  * 以LOCAL_开始的变量名（比如LOCAL_MODULE）

  * 以PRIVATE_,NDK_,或者APP_开始的变量名（内部使用）

  * 小写变量名（内部使用，比如my-dir)

如果你需要在Android.mk中定义你自己的方便使用的变量名，我们推荐使用MY_前缀，一个普通的例子：

	MY_SOURCES := foo.c
	ifneq ($(MY_CONFIG_BAR),)
		MY_SOURCES += bar.c
	endif

	LOCAL_SRC_FILES += $(MY_SOURCES)

好了，我们现在去看看：

## NDK提供的变量

这些GNU MAKE 变量，在你的Android.mk被解析之前，是被构建系统创建的。注意在一定的特殊的情形下，NDK可能要解析你的Android.mk文件几次，每次用这些变量中的一些不同的定义。

### CLEAR_VARS

指向了一个构建脚本，这个脚本几乎取消定义在模块描述部分定义的所有LOCAL_XXX变量，在开始一个新模块之前，你必须包含这个脚本。包含代码如下：

	include $(CLEAR_VARS)

### BUILD_SHARED_LIBRARY

指向了一个构建脚本，这个脚本搜集你在LOCAL_XXX变量中提供的这个模块的所有信息，决定如何从你列出的源码中建立一个动态库。注意在包含这个文件前，最少你必须有LOCAL_MODULE和LOCAL_SRC_FILES定义。用法示例：
	
	include $(BUILD_SHARED_LIBRARY)

注意这将长生一个名字为lib.so的文件。

### BUILD_STATIC_LIBRARY

BUILD_SHARED_LIBRARY的一个变体，通常生成一个静态库代替动态库。静态库是不会被拷到你的/project/packages下，但是可以用来建立一个动态库（下面将会看到LOCAL_STATIC_LIBRARY和LOCAL_WHOLE_STATIC_LIBRARY的描述），用法如下：

        include $(BUILD_STATIC_LIBRARY)

这将生成一个叫做lib.a的文件。

### PREBUILD_SHARED_LIBRARY

指向一个构建脚本，这个脚本通常是指定一个预建的动态库。不像BUILD_SHARED_LIBRARY和BUILD_STATIC_LIBRARY那样，LOCAL_SRC_FILES的值必须是一个动态库的单个路径（像foo/libfoo.so），代替一个源码文件。

你可以参考一个预建库在另一个用LOCAL_PREBUILT变量的模块中。

### PREBUILD_STATIC_LIBRARY

类似与PREBUILD_SHARED_LIBRARY，不过是用静态库代替。

### TARGET_ARCH

目标板CPU体系结构的名字，它是由Android开放源代码项目指定的。这是任何arm兼容构建的arm，独立于CPU体系结构的修订。

### TARGET_PLATFORM

当Android.mk解析时，目标板android平台的名字。例如，android-3对应于Android 1.5 系统镜像。

### TARGET_ARCH_ABI

当Android.mk被解析时，目标板CPU+ABI的名字。你可以指定下列值的一个或者多个：

	armeabi
		For ARMv5TE
	
	armeabi-v7a
		For ARMv7
	
	arm64-v8a
		For ARMv8 AArch64
	
	x86
		For i686
	
	x86_64
		For x86-64
	
	mips
		For mips32 (r1)
	
	mips64
		For mips64 (r6)

 * 注意：在大于android ndk 1.6_rc1，这个变量是简单的被定义为arm。然而这个值已经被重新定义为了较好的匹配被Anroid平台用的形式。

 注意所有ARM-based ABI将使TARGET_ARCH定义到arm，但是可能有不同的TARGET_ARCH_ABI。

### TARGET_ABI

目标平台和ABI的连接，它被定义作为-，当你想为一个真实的设备测试一个指定的目标系统镜像时是有用的。

默认，这将是android-3-armeabi。Android NDK 1.6_rc1版本以上的，默认是android-3-arm。

## NDK提供的函数宏

下面这些是GNU Make函数宏，必须通过调用'$(call <function>)'来执行。他们返回文本形式的信息。

### my-dir

返回最后包含Makefile的路径，典型的是当前Android.mk的目录。这通常使用来在Android.mk文件的开始定义LOCAL_PATH的。用法如下：

	LOCAL_PATH := $(call my-dir)

 * 特别注意：由于GNU Make工作的方式，在解析构建脚本的过程中将真的返回最后一个包含Makefile的路径。在包含另外一个文件之后，不要调用my-dir。

 例如，考虑下面的例子：

	LOCAL_PATH := $(call my-dir)

	... declare one module

	include $(LOCAL_PATH)/foo/`Android.mk`

	LOCAL_PATH := $(call my-dir)

	... declare another module

这里的难题是第二个call my-dir将定义LOCAL_PATH到$PATH/foo代替$PATH，归因于在那之前，include是执行完了的。由于这个原因，放添加的语句包含，在Android.mk每件事情之后，像下面这样：

	LOCAL_PATH := $(call my-dir)

	... declare one module

	LOCAL_PATH := $(call my-dir)

	... declare another module

	# extra includes at the end of the `Android.mk`
	include $(LOCAL_PATH)/foo/`Android.mk`

如果这是不方便的，保存第一个my-dir调用的值到另外一个变量，例如：

	MY_LOCAL_PATH := $(call my-dir)

	LOCAL_PATH := $(MY_LOCAL_PATH)

	... declare one module

	include $(LOCAL_PATH)/foo/`Android.mk`

	LOCAL_PATH := $(MY_LOCAL_PATH)

	... declare another module

### all-subdir-makefiles

返回一个在当前my-dir所有子目录中的Android.mk，例如，系列性地考虑下面：

	sources/foo/Android.mk
	sources/foo/lib1/Android.mk
	sources/foo/lib2/Android.mk

如果sources/foo/Android.mk包含这样的单行：

	include $(call all-subdir-makefiles)

它将自动包含sources/foo/lib1/Android.mk和sources/foo/lib2/Android.mk

这个函数将被用来为构建系统提供深层嵌套源码目录系列。注意默认，NDK只查找文件/sources/*/Android.mk

### this-makefile

返回当前makefile的路径（例如这个函数被调用的地方）

### parent-makefile

返回包裹体树中父Makefile的路径，例如包含当前这个makefile文件的makefile文件的路径。

### grand-parent-makefile

自己猜吧。

### import-module

这个函数允许你通过名字发现和包含另一个模块的Android.mk。一个经典的例子如下：

	$(call import-module,<name>)

这将在你的NDK_MODULE_PATH环境变量的列表中查找被标记为<name>的模块。并且自动为你包含他的Android.mk文件。

## 模块描述变量

下面这些变量用来为构建系统描述你的模块，你应该在两个include中间定义他们中的一些。就像先前写的，一个脚本将取消定义或者清楚这些变量中的所有，除非在它们的描述中明确提到不清除的变量。

### LOCAL_PATH

这个变量通常给出当前文件的路径。你必须在你Android.mk文件的开始定义它。就像下面这样做的：

	LOCAL_PATH := $(call my-dir)
	
这个变量不会被清除，因此在Android.mk文件中只有一个定义是必要的（在单个文件中定义多个模块）。

### LOCAL_MODULE

这是你模块的名字。它在所有模块名字中必须是唯一的，不要包含任何空格。在包含任何脚本之前你必须定义它。

默认情况下，这个模块的名字决定生成文件的名字，例如lib<foo>.so是模块foo的动态库。然而你在你的NDK构建文件（Android.mk或Applicaton.mk）中应该只可以用它们正常的名字参考它们的模块。

你可以重写用LOCAL_MODULE_FILENAME这个默认生成文件，下面会提到。

### LOCAL_MODULE_FILENAME

这个变量是可选的，允许你重新定义生成文件的名字。默认情况下，模块<foo>将总是生成静态库lib<foo>.a和动态库lib<foo>.so，这是标准unix转换。

你可以通过定义LOCAL_MODULE_FILENAME重写这个默认。例如：

	LOCAL_MODULE := foo-version-1
	LOCAL_MODULE_FILENAME := libfoo

 * 注意：你不应该放一个路径或者文件扩展在你的LOCAL_MODULE_FILENAME中，这些将通过构建系统自动处理。

### LOCAL_SRC_FILES

这是一个建立你的模块的源文件列表。只列出那些传给编译器的文件，构建系统将自动为你处理依赖关系。

注意源码文件和LOCAL_PATH的关系，你可以用路径组建。比如：

   LOCAL_SRC_FILES := foo.c \
					toto/bar.c

绝对文件路径也是支持的：

	LOCAL_SRC_FILES := /home/user/mysources/foo.c

或者在window下：

	LOCAL_SRC_FILES := c:/Users/user/sources/foo.c

不推荐使用绝对路径。这样能使你的Android.mk在不同的根文件系统的重用更容易。

 * 注意：在构建文件中总是用unix风格的/.windows格式的\不会被合理的处理。


