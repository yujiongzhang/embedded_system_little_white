
#!/bin/bash

echo "🚀 git clone ..."

git clone https://github.com/luokyme/NetAssistant.git

echo "🚀 make project ..."

cd NetAssistant

qmake

make

echo "✅ done"


