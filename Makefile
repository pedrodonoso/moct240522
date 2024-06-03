build-jens gen-jens: program = jens
build-jens run-jens gen-jens: program_name = jens
build-moct gen-moct, compare-moct: program = moct 
build-moct run-moct run-moct2 run-moct3 run-moct-valgrind run-moct-gdb gen-moct, compare-moct: program_name = mesher_roi

.PHONY: help
help:
	@echo "install, build-jens, build-moct, run-jens, run-moct, validate-jens, validate-moct"

.PHONY: install
install:
	apt install -y cmake make
	sudo apt-get install -y build-essential

.PHONY: build-moct
build-moct: 
	rm -rf ./${program_name}
	cmake -DCMAKE_BUILD_TYPE=Debug -B build/ -S src/ && make -C build/ && cp build/${program_name} ./

.PHONY: run-moct
run-moct:
	./${program_name} -d ./data/cortex.mdl -s 5 -r ./data/cortex_surf_roi.mdl 7 -u c_5r7 -m -v

.PHONY: run-moct2
run-moct2:
	./${program_name} -d ./data/cortex.mdl -c ./c_5r7.oct -l ./c_5r7.ref -u c_5r7_2 -m -v

.PHONY: run-moct3
run-moct3:
	./${program_name} -d ./data/cortex.mdl -c ./c_5r7_2.oct -l ./c_5r7_2_to_refine.ref -u c_5r7_3 -m -v

.PHONY: run-moct-gdb
run-moct-gdb:
	gdb ./${program_name}
# run -d ./data/cortex.mdl -s 5 -r ./data/cortex_surf_roi.mdl 7 -u c_5r7 -m -v

