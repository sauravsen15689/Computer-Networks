set val(nn)    12
set val(stop)  150   

set ns [new Simulator]

set file1 [open aodv.tr w]
$ns trace-all $file1

set file2 [open aodv.nam w]
$ns namtrace-all-wireless $file2 500 400

set topo [new Topography]
$topo load_flatgrid 500 400

create-god $val(nn)

$ns node-config -adhocRouting AODV \
                 -llType LL \
                 -macType Mac/802_11 \
                 -ifqType Queue/DropTail/PriQueue \
                 -ifqLen 50 \
                 -antType Antenna/OmniAntenna \
                 -propType Propagation/TwoRayGround \
                 -phyType Phy/WirelessPhy \
                 -channel [new Channel/WirelessChannel] \
                 -topoInstance $topo \
                 -agentTrace ON \
                 -routerTrace ON \
                 -macTrace ON \
                 -movementTrace ON

	
    for {set i 0} {$i < $val(nn) } { incr i } {
        set node_($i) [$ns node]
        $node_($i) set X_ [ expr 10+round(rand()*480) ]
        $node_($i) set Y_ [ expr 10+round(rand()*380) ]
        $node_($i) set Z_ 0.0
    }

    for {set i 0} {$i < $val(nn) } { incr i } {
        $ns at [ expr 15+round(rand()*60) ] "$node_($i) setdest [ expr 10+round(rand()*480) ] [ expr 10+round(rand()*380) ] [ expr 2+round(rand()*15) ]"
        
    }

# Generation of movements
# $ns at 10.0 "$node_(0) setdest 250.0 250.0 3.0"
# $ns at 15.0 "$node_(1) setdest 45.0 285.0 5.0"
# $ns at 70.0 "$node_(2) setdest 480.0 300.0 5.0"
# $ns at 20.0 "$node_(3) setdest 200.0 200.0 5.0"
# $ns at 25.0 "$node_(4) setdest 50.0 50.0 10.0"
# $ns at 60.0 "$node_(5) setdest 150.0 70.0 2.0"
# $ns at 90.0 "$node_(6) setdest 380.0 150.0 8.0"
# $ns at 42.0 "$node_(7) setdest 200.0 100.0 15.0"
# $ns at 55.0 "$node_(8) setdest 50.0 275.0 5.0"
# $ns at 19.0 "$node_(9) setdest 250.0 250.0 7.0"
# $ns at 90.0 "$node_(10) setdest 150.0 150.0 20.0"

# Set a TCP connection between node_(2) and node_(8)
set tcp [new Agent/TCP/Newreno]
$tcp set class_ 2
set sink [new Agent/TCPSink]
$ns attach-agent $node_(2) $tcp
$ns attach-agent $node_(8) $sink
$ns connect $tcp $sink
set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ns at 10.0 "$ftp start"

# Define node initial position in nam
for {set i 0} {$i < $val(nn)} { incr i } {
$ns initial_node_pos $node_($i) 30
}

# Telling nodes when the simulation ends
for {set i 0} {$i < $val(nn) } { incr i } {
    $ns at $val(stop) "$node_($i) reset";
}

# ending nam and the simulation
$ns at $val(stop) "$ns nam-end-wireless $val(stop)"
$ns at $val(stop) "stop"
$ns at 150 "puts \"end simulation\" ; $ns halt"
proc stop {} {
    global ns file1 file2
    $ns flush-trace
    close $file1
    close $file2
    exec nam aodv.nam &
    exit 0
}

$ns run