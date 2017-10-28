set ns [new Simulator]

$ns color 1 Blue

set file1 [open congestion.tr w]
$ns trace-all $file1

set file2 [open congestion.nam w]
$ns namtrace-all $file2

proc finish {} {
	global ns file1 file2
	$ns flush-trace
	close $file1
	close $file2
	exec nam congestion.nam &
	exit 0
}

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]

$n1 color red
$n1 shape box

$ns duplex-link $n0 $n2 2Mb 10ms DropTail
$ns duplex-link $n1 $n2 2Mb 10ms DropTail
$ns duplex-link $n2 $n3 2Mb 10ms DropTail

set lan [$ns newLan "$n3 $n4 $n5" 0.3Mb 30ms LL Queue/DropTail MAC/Csma/Cd Channel]

$ns duplex-link-op $n0 $n2 orient right-down
$ns duplex-link-op $n1 $n2 orient right-up
$ns duplex-link-op $n2 $n3 orient right

set tcp [new Agent/TCP]
$ns attach-agent $n0 $tcp
set tsink [new Agent/TCPSink]
$ns attach-agent $n4 $tsink
$ns connect $tcp $tsink
$tcp set fid_ 1

$ns queue-limit $n2 $n3 10

set ftp [new Application/FTP]
$ftp attach-agent $tcp 

proc plot {tcpsource file3} {
	global ns
	set conges [$tcpsource set cwnd_]
	set now [$ns now]
	puts $file3 "$now $conges"
	$ns at [expr $now+0.1] "plot $tcpsource $file3"

}

$ns at 0.1 "$ftp start"
$ns at 124.5 "$ftp stop"

set svpoint [open congestion.xg w]
$ns at 1.0 "plot $tcp $svpoint"

$ns at 125 "finish"
$ns run