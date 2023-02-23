build:
	javac -d classes src/rbt/*java src/hmr/*.java src/hmo/*.java src/hmc/*.java src/hashing/*.java

run-best: run-p2

run-p1: build
	java -cp classes hmo.HMDMain

run-p2: build
	java -cp classes rbt.RBTMain

run-others: build
	java -cp classes hmc.HMCMain
	java -cp classes hmr.HMRMain

clean:
	rm -rf classes/*
	rm out/*.out*
