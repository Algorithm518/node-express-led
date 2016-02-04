Vagrant.configure(2) do |config|
    config.vm.box = "ubuntu/trusty64"
    config.vm.synced_folder "./node-led", "/home/vagrant/node-led", create:true
    config.vm.network "forwarded_port", guest: 3000, host: 12804
    config.vm.provision :shell, :path => "setup.sh"
    config.vm.provider "virtualbox" do |vb|
        vb.memory = "2048"
    end
end