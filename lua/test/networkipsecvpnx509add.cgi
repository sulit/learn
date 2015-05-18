#!/usr/bin/lua

local frame = require "frame"
local common = require "common"
local confignet = require "confignet"
local networkconfig = require "networkconfig"
local networkipsecvpn = require "networkipsecvpn"

local logined = common.checkauth()
if logined == 1 then

local onloadstr = ""
frame.printsubhead()
frame.printsubbody(onloadstr)

local conf = common.gethtmlvalue()
---[==[
if conf ~= nil then
	--[=[
	for k,v in pairs(conf) do
		print(k,v.."<br />")
	end
	--]=]
	--networkconfig.ipsecvpn_add_x509_set(conf)	
	networkconfig.ipsecvpn_ca_set(conf)
end
--]==]

local lines = common.getrun()
local rules = networkipsecvpn.getipsecrule(lines)
networkipsecvpn.getipsecvpnconf(rules)

local function printjscss()
	print([[
		<script>
		$(document).ready(function(){
			$("#caserverurlstr").change(function(){
				if($("#caserverurlstr").val()=="")
				{
					alert("证书服务器地址不能为空！");
					return false;
				}
			]])
	if conf and conf.ike then
		local f1 = io.open("/u/cert/caCert"..conf.ike.."-0")
		local f2 = io.open("/u/cert/caCert"..conf.ike.."-1")
		local f3 = io.open("/u/cert/caCert"..conf.ike.."-2")
		if f1 ~= nil or f2 ~= nil or f3 ~= nil then
			print([[
				if(!confirm("在改变服务器地址后，先前的服务器的文件将失效，后台将帮你清除，你确定要更改吗?"))
				{
					$("#caserverurlstr").val($("#oldcaserverurlstr").val());
					return false;
				}
			]])
		end
		if f1 ~= nil then
			io.close(f1)
		end
		if f2 ~= nil then
			io.close(f2)
		end
		if f3 ~= nil then
			io.close(f3)
		end

	end

	print([[
					$.post("networkipsecvpnstatus.cgi",{caserverurlstr : $("#caserverurlstr").val(),ike:$("#ike").val()},function(data,statusText){
						//alert(data);

						//alert(typeof(data));
						var caserverurlstrdata = data.caserverurlstr;
						if(caserverurlstrdata=="bad")
						{
							$("#note").remove();
							var $note = $("<span id='note'><input type='hidden' name='caserverurlstrflag' value='bad' ><font color='red'><b>CA服务器地址不正确，或者网络不通，请检查</b></font></span>");
							$("#caserverurlstr").after($note);
						}
						else if(caserverurlstrdata=="ok")
						{
							$("#note").remove();
							var $note = $("<span id='note'><input type='hidden' name='caserverurlstrflag' value='ok' ><font color='green'><b>正确</b></font></span>");
							$("#caserverurlstr").after($note);
						}
					},"json");
			});

			if($("#ikelocalcertfileproducestyletd").val() == "auto")
			{
				$(".certfileechodiv").removeClass("certfileechodiv").addClass("certfilehiddendiv");
			}
			else if($("#ikelocalcertfileproducestyletd").val() == "mando")
			{
				$(".certfilehiddendiv").removeClass("certfilehiddendiv").addClass("certfileechodiv");
			}
	
			if($("#ikelocalprikeyfileproducestyletd").val() == "auto")
			{
				$(".prikeyfechodiv").removeClass("prikeyfechodiv").addClass("prikeyfhiddendiv");
				$(".prikeylhiddendiv").removeClass("prikeylhiddendiv").addClass("prikeylechodiv");
			}
			else if($("#ikelocalprikeyfileproducestyletd").val() == "mando")
			{
				$(".prikeylechodiv").removeClass("prikeylechodiv").addClass("prikeylhiddendiv");
				$(".prikeyfhiddendiv").removeClass("prikeyfhiddendiv").addClass("prikeyfechodiv");
			}

			$("#ikelocalcertfileproducestyletd").change(function(){
				if(this.value=="auto")
				{
					$(".certfileechodiv").removeClass("certfileechodiv").addClass("certfilehiddendiv");
				}
				else if(this.value=="mando")
				{
					$(".certfilehiddendiv").removeClass("certfilehiddendiv").addClass("certfileechodiv");
				}
			});
			$("#ikelocalprikeyfileproducestyletd").change(function(){
				if(this.value=="auto")
				{
					$(".prikeyfechodiv").removeClass("prikeyfechodiv").addClass("prikeyfhiddendiv");
					$(".prikeylhiddendiv").removeClass("prikeylhiddendiv").addClass("prikeylechodiv");
				}
				else if(this.value=="mando")
				{
					$(".prikeylechodiv").removeClass("prikeylechodiv").addClass("prikeylhiddendiv");
					$(".prikeyfhiddendiv").removeClass("prikeyfhiddendiv").addClass("prikeyfechodiv");
				}
			});
		});
	</script>
	<style>
	.certfileechodiv,.prikeyfechodiv,.prikeylechodiv{
		display:inline;
	}
	.certfilehiddendiv,.prikeyfhiddendiv,.prikeylhiddendiv{
		display:none;
	}
	</style>
	]])
end

local function printipsecvpn_ike()
	print([[<tr>]])
	print([[<td width="10%">IKE标识号：</td>]])
	print([[<td width="30%">]])
	if conf ~= nil then
		print([[<input type="hidden" name="oldike" value=]])
		print(conf.ike)
		print([[ />]])
	end
	print([[<select id="ike" name="ike">]])
	local t = common.ikeconf
	--print("<option value=\"" .. "ike" .. "\">" .. "ike" .. "</option>")
	for i,j in pairs(t) do
			local ike = nil
			local ikeauthenticationmethod = nil
			if j ~= nil then
				for x,y in pairs(j) do
					if x ~= nil and y ~= nil then
						if x == "ike" then
							ike = y
						elseif x == "ikeauthenticationmethod" then
							ikeauthenticationmethod = y
						end
					end
				end
				if ike ~= nil and ikeauthenticationmethod =="ca" then
					if conf ~= nil then
						if tonumber(ike) == tonumber(conf.ike) then
							--print([[<script>alert("hello1");</script>]])
							print("<option value=\"" .. conf.ike .. "\" selected='selected'>" .. conf.ike .. "</option>")
						else
							--print([[<script>alert("hello2");</script>]])
							print("<option value=\"" .. ike .. "\">" .. ike .. "</option>")
						end
					else
							--print([[<script>alert("hello3");</script>]])
						print("<option value=\"" .. ike .. "\">" .. ike .. "</option>")
					end
				end
			end
		end
	print([[</select></td>]])
	print([[</tr>]])
end

local function printipsecvpn_ca_url()
	print([[<tr> ]])
	print([[<td width="10%">证书服务器地址(URL)：</td>]])
	if conf ~= nil then
		print([[<td width="30%">]])
		print([[<input type="hidden" id="oldcaserverurlstr" name="oldikecaurl" value=]])
		print(conf.ikecaurl)
		print([[ />]])
		print("<input type='text' id= 'caserverurlstr' name='ikecaurl' value='".. conf.ikecaurl.."' >")
	else
		print([[<td width="30%">
			<input type="text" id="caserverurlstr" name="ikecaurl" value="" >
		]])
	end
	print([[</td>]])
	print([[</tr>]])
end

local function printipsecvpn_local_cert_file()
---[==[
	print([[<tr>]])
	print([[<td width="10%">本地证书文件生成方式：</td>]])
	--print([[<td><select name="ikelocalcertfileproducestyle" id="ikelocalcertfileproducestyletd" onchange="selectsubjs('certfile',this.options[this.options.selectedIndex].value)" property="value">]])
	print([[<td><select name="ikelocalcertfileproducestyle" id="ikelocalcertfileproducestyletd"  property="value">]])
	print([[<option value="auto">自动</option>]])
	print([[<option value="mando" ]])
	if conf ~= nil then
		if conf.ikelocalcertfile ~= "auto" then
			print([[selected = "selected"]])
		end
	end
	print([[>手动</option>]])
	print([[</select></td>]])
	print([[</tr>]])
--]==]
	--print([[<div class="hiddendiv">]])
	print([[<tr> ]])
	print([[<td width="10%" class="certfilehiddendiv">本地证书文件：</td>]])
	if conf ~= nil and conf.ikelocalcertfile ~= "auto" then
		print([[<td width="30%" class="certfilehiddendiv">]])
		print([[<input type="hidden" name="oldikelocalcertfile" value=]])
		print(conf.ikelocalcertfile)
		print([[ />]])
		print("<input type='text' name='ikelocalcertfile' value='"..conf.ikelocalcertfile.."' />")
	else
		print([[<td width="30%" class="certfilehiddendiv">
			<input type="text" name="ikelocalcertfile" />
		]])
	end
	print([[</td>]])
	print([[</tr>]])
	--print([[</div>]])
end

local function printipsecvpn_peer_cert_file()
	print([[<tr> ]])
	print([[<td width="10%">对端证书文件：</td>]])
	if conf ~= nil then
		print([[<td width="30%">]])
		print([[<input type="hidden" name="oldikepeercertfile" value=]])
		print(conf.ikepeercertfile)
		print([[ />]])
		print("<input type='text' name='ikepeercertfile' value='"..conf.ikepeercertfile.."' />")
	else
		print([[<td width="30%">
			<input type="text" name="ikepeercertfile" />
		]])
	end
	print([[</td>]])
	print([[</tr>]])
end

local function printipsecvpn_local_prikey_file()
---[==[
	print([[<tr>]])
	print([[<td width="10%">本地私钥文件生成方式：</td>]])
	--print([[<td><select name="ikelocalprikeyfileproducestyle" id="ikelocalprikeyfileproducestyletd" onchange="selectsubjs('prikey',this.options[this.options.selectedIndex].value)" property="value">]])
	print([[<td><select name="ikelocalprikeyfileproducestyle" id="ikelocalprikeyfileproducestyletd"  property="value">]])
	print([[<option value="auto">自动</option>]])
	print([[<option value="mando" ]])
	if conf ~= nil then
		if conf.ikelocalprikeyfile ~= "auto" then
			print([[selected = "selected"]])
		end
	end
	print([[>手动</option>]])
	print([[</select></td>]])
	print([[</tr>]])
--]==]

	print([[<tr> ]])
	print([[<td width="10%" class="prikeyfhiddendiv">本地私钥文件：</td>]])
	if conf ~= nil and conf.ikelocalprikeyfile ~= "auto" then
		print([[<td width="30%" class="prikeyfhiddendiv">]])
		print([[<input type="hidden" name="oldikelocalprikeyfile" value=]])
		print(conf.ikelocalprikeyfile)
		print([[ />]])
		print("<input type='text' name='ikelocalprikeyfile' value='"..conf.ikelocalprikeyfile.."' />")
	else
		print([[<td width="30%" class="prikeyfhiddendiv">
			<input type="text" name="ikelocalprikeyfile" />
		]])
	end
	print([[</td>]])
	print([[</tr>]])
end

local function printipsecvpn_local_prikey_file_len()
	print([[<tr> ]])
	print([[<td width="10%" class="prikeylechodiv">本地私钥文件长度：</td>]])
	if conf ~= nil and conf.ikelocalprikeyfilelen ~= "auto" then
		print([[<td width="30%" class="prikeylechodiv">]])
		print([[<input type="hidden" name="oldikelocalprikeyfilelen" value=]])
		print(conf.ikelocalprikeyfilelen)
		print([[ />]])
		print("<input type='text' name='ikelocalprikeyfilelen' value='"..conf.ikelocalprikeyfilelen.."' />")
	else
		print([[<td width="30%" class="prikeylechodiv">
			<input type="text" name="ikelocalprikeyfilelen" value="2048" />(512-2048)
		]])
	end
	print([[</td>]])
	print([[</tr>]])
end

local function printipsecvpn_cert_attr()
	if conf ~= nil then
		print([[<tr><td width="10%">名字：</td>]])
		print([[<td width="30%">]])
		print([[<input type="hidden" name="oldcommon_name" value=]])
		print(conf.common_name)
		print([[ >]])
		print("<input type='text' name='common_name' value='"..conf.common_name.."' >")
		print([[</td></tr>]])
		print([[<tr><td width="10%">部门：</td>]])
		print([[<td width="30%">]])
		print([[<input type="hidden" name="oldorganization_unit" value=]])
		print(conf.organization_unit)
		print([[ >]])
		print("<input type='text' name='organization_unit' value='"..conf.organization_unit.."' >")
		print([[</td></tr>]])
		print([[<tr><td width="10%">组织：</td>]])
		print([[<td width="30%">]])
		print([[<input type="hidden" name="oldorganization" value=]])
		print(conf.organization)
		print([[ >]])
		print("<input type='text' name='organization' value='"..conf.organization.."' >")
		print([[</td></tr>]])
		print([[<tr><td width="10%">地区：</td>]])
		print([[<td width="30%">]])
		print([[<input type="hidden" name="oldlocality" value=]])
		print(conf.locality)
		print([[ >]])
		print("<input type='text' name='locality' value='"..conf.locality.."' >")
		print([[</td></tr>]])
		print([[<tr><td width="10%">国家：</td>]])
		print([[<td width="30%">]])
		print([[<input type="hidden" name="oldcountry" value=]])
		print(conf.country)
		print([[ >]])
		print("<input type='text' name='country' value='"..conf.country.."' >")
		print([[</td></tr>]])
	else
		print([[<tr><td width="10%">名字：</td>]])
		print([[<td width="30%">
			<input type="text" name="common_name">
		</td></tr>]])
		print([[<tr><td width="10%">部门：</td>]])
		print([[<td width="30%">
			<input name="organization_unit">
		</td></tr>]])
		print([[<tr><td width="10%">组织：</td>]])
		print([[<td width="30%">
			<input name="organization">
		</td></tr>]])
		print([[<tr><td width="10%">地区：</td>]])
		print([[<td width="30%">
			<input name="locality">
		</td></tr>]])
		print([[<tr><td width="10%">国家：</td>]])
		print([[<td width="30%">
			<input name="country">
		</td></tr>]])
	end
end

print([[
<form id="formnetworkipsecvpnx509add" action="networkwaitinfo.cgi" method="post">
<table width="100" align="left"  border="0" style="float: left;">
]])

printjscss()
printipsecvpn_ike()
printipsecvpn_ca_url()
printipsecvpn_local_cert_file()
printipsecvpn_peer_cert_file()
printipsecvpn_local_prikey_file()
printipsecvpn_local_prikey_file_len()
printipsecvpn_cert_attr()
print([[</table>]])
print([[<tr>]])
print([[<td><input type="hidden" name="caset" value="yes" /><input type="button" name="saveconfig" value="保存配置" onclick="check_networkipsecvpn_x509add_data()" /></td>]])
print([[<td> <input type="button" name="saveconfig" value="返回" onclick="location='networkipsecvpndataauth.cgi'"/></td>]])
if conf ~= nil then
	print("<td> <input type='button' name='requestcacert' value='请求CA证书' onclick='check_networkipsecvpn_request_cacert(\""..conf.ike.."\")' /></td>")
end
print([[</tr>]])
print([[</form>]])

frame.printsubend()

end
