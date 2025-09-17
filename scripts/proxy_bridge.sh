#!/bin/bash
# 初始化变量
host_ip=""
wslip=$(hostname -I | awk '{print $1}')
port=7890
PROXY_HTTP=""

# 设置代理函数
set_proxy(){
  if read -t 30 -p "Please enter your host ip address in 30s: " input_host_ip
  then
    echo "host_ip is :$input_host_ip"
    PROXY_HTTP="http://${input_host_ip}:${port}"
    
    export http_proxy="${PROXY_HTTP}"
    export HTTP_PROXY="${PROXY_HTTP}"

    export https_proxy="${PROXY_HTTP}"
    export HTTPS_PROXY="${PROXY_HTTP}"

    export ALL_PROXY="${PROXY_HTTP}"
    export all_proxy=${PROXY_HTTP}

    git config --global http.https://github.com.proxy ${PROXY_HTTP}
    git config --global https.https://github.com.proxy ${PROXY_HTTP}
    echo "Proxy has been opened."

    # 将 PROXY_HTTP 写入配置文件以便测试函数读取
    echo "${PROXY_HTTP}" > /tmp/proxy_http.conf
  else
    echo
    echo "sorry, time out!"
  fi
}

# 取消代理函数
unset_proxy(){
  unset http_proxy
  unset HTTP_PROXY
  unset https_proxy
  unset HTTPS_PROXY
  unset ALL_PROXY
  unset all_proxy
  git config --global --unset http.https://github.com.proxy
  git config --global --unset https.https://github.com.proxy

  echo "Proxy has been closed."

  # 删除配置文件
  rm -f /tmp/proxy_http.conf
}

# 测试代理设置函数
test_setting(){
  if [ -f /tmp/proxy_http.conf ]; then
    PROXY_HTTP=$(cat /tmp/proxy_http.conf)
  else
    echo "Proxy is not set. Please run './proxy_bridge.sh set' first."
    exit 1
  fi

  echo "WSL IP:" ${wslip}
  echo "Proxy HTTP:" ${PROXY_HTTP}
  echo "Try to connect to Google with proxy..."

  curl -I -x ${PROXY_HTTP} http://www.google.com
  resp=$(curl -I -s --connect-timeout 5 -m 5 -w "%{http_code}" -o /dev/null -x ${PROXY_HTTP} http://www.google.com)
  if [ ${resp} = 200 ]; then
    echo "Proxy setup succeeded!"
  else
    echo "Proxy setup failed with response code: ${resp}"
  fi
}

# 脚本入口，根据传入的参数执行相应功能
if [ "$1" = "set" ]
then
  set_proxy

elif [ "$1" = "unset" ]
then
  unset_proxy

elif [ "$1" = "test" ]
then
  test_setting
else
  echo "Unsupported arguments."
fi

