build: trial rise redemption create_files

run_trial:
	java Trial

run_rise:
	java Rise

run_redemption:
	java Redemption

trial: Trial.java Task.java
	javac $^

rise: Rise.java Task.java
	javac $^

redemption: Redemption.java Task.java
	javac $^

create_files:
	touch sat.sol sat.cnf

clean:
	rm -f *.class sat.*

.PHONY: build clean
