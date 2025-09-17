#!/bin/bash

# 函数：打开代理
enable_proxy() {
    export http_proxy='http://localhost:7897'
    export https_proxy='http://localhost:7897'
    export ALL_PROXY='socks5://localhost:7897'

    sudo bash -c 'echo "http_proxy=http://localhost:7897" >> /etc/environment'
    sudo bash -c 'echo "https_proxy=http://localhost:7897" >> /etc/environment'
    sudo bash -c 'echo "ALL_PROXY=socks5://localhost:7897" >> /etc/environment'

    echo "Proxy has been enabled."
    echo "Current proxy settings:"
    env | grep -i proxy

    echo "Testing HTTP connection without proxy..."
    curl -I http://www.google.com

    echo "Testing SOCKS connection without proxy..."
    curl -I --socks5 localhost:7897 http://www.google.com
}

# 函数：关闭代理
disable_proxy() {
    unset http_proxy
    unset https_proxy
    unset ALL_PROXY

    sudo sed -i '/http_proxy/d' /etc/environment
    sudo sed -i '/https_proxy/d' /etc/environment
    sudo sed -i '/ALL_PROXY/d' /etc/environment

    echo "Proxy has been disabled."
    echo "Current proxy settings:"
    env | grep -i proxy
}

# 检查传递的参数
if [ "$1" == "enable" ]; then
    enable_proxy
elif [ "$1" == "disable" ]; then
    disable_proxy
else
    echo "Usage: $0 {enable|disable}"
    echo "  enable   - Enable the proxy"
    echo "  disable  - Disable the proxy"
fi

