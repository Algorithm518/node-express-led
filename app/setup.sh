sudo apt-get -y update
sudo apt-get -y install build-essential
curl -so node.tar.gz https://nodejs.org/dist/v4.2.6/node-v4.2.6-linux-x64.tar.xz
sudo tar -C /usr/local --strip-components 1 -xvf node.tar.gz && rm node.tar.gz
sudo npm install node-pre-gyp -g
cd app && npm install --no-bin-links
