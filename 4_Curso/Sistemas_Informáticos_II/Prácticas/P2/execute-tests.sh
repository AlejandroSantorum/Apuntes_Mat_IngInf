#!/usr/bin/env bash

for iter in 1750 2000 2250 2500 #1 250 500 750 1000 1250 1500 1750 2000 2250 2500
do
    echo 'RUNNING ' $iter 'ITERATION!!!!'
    # Configure new test
    echo '###### Configure new test'
    sed -i "s#<stringProp name=\"ThreadGroup.num_threads\">.*</stringProp>#<stringProp name=\"ThreadGroup.num_threads\">$iter</stringProp>#" P2-curvaProductividad.jmx
    # Register vmstat
    echo '###### Monitoring CPU usage on HOST'
    nohup vmstat -n 1 | (trap '' INT; awk '{print; if(NR>2) cpu+=$13+$14;}END{print"MEDIA";print "NR: ",NR,"CPU: ", cpu/(NR-2);}';) > cpu-host.txt &
    # Launch vmstat and si2-monitor after waiting time
    echo '###### Monitoring CPU usage and launching si2-monitor on VM2'
    ssh si2@10.1.7.2 'source si2.source; ~/run-monitor.sh' &
    # Run tests
    echo '###### Running tests'
    ~/apache-jmeter-5.2.1/bin/jmeter -n -t P2-curvaProductividad.jmx -l test-results.jtl
    # Kill stuff
    echo '###### Terminating monitoring processes on VM2 and HOST'
    ssh si2@10.1.7.2 'source si2.source; ~/stop-monitor.sh'
    pkill vmstat
    # Collect data
    echo '###### Collecting data'
    scp si2@10.1.7.2:~/cpu.txt cpu-vm.txt
    scp si2@10.1.7.2:~/result.txt monitor.txt
    ssh si2@10.1.7.2 'rm ~/cpu.txt ~/result.txt'
    ssh si2@10.1.7.1 "psql visa -U alumnodb -c 'DELETE FROM PAGO'"
    echo '###### Structuring stuff'
    mv cpu-vm.txt cpu-host.txt monitor.txt test-results.jtl data-ex-9/$iter\u
done
