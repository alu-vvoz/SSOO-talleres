cmd_/vagrant/taller3/alumnos/azar/azar.ko := ld -r -m elf_x86_64  -z max-page-size=0x200000 -z noexecstack   --build-id  -T ./scripts/module-common.lds -o /vagrant/taller3/alumnos/azar/azar.ko /vagrant/taller3/alumnos/azar/azar.o /vagrant/taller3/alumnos/azar/azar.mod.o;  true
