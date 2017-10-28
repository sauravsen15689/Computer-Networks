set ns [new Simulator]

$ns color 1 Blue
$ns color 2 Red

set file1 [open mtraffic.tr w]
$ns trace-all $file1

set file2 [open mtraffic.nam w]
$ns namtrace-all $file2

proc finish {} {
	global ns file1 file2
	$ns flush-trace
	close $file1
	close $file2
	exec nam mtraffic.nam &
	exit 0
}

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]

$ns at 1.0 "$n0 label \"FTP\""
$ns at 0.1 "$n1 label \"CBR\""

$ns duplex-link $n0 $n2 2Mb 10ms DropTail
$ns duplex-link $n1 $n2 2Mb 10ms DropTail
$ns duplex-link $n2 $n3 0.5Mb 70ms DropTail
$ns duplex-link $n3 $n4 0.7Mb 30ms DropTail
$ns duplex-link $n3 $n5 0.7Mb 30ms DropTail

$ns duplex-link-op $n0 $n2 orient right-down
$ns duplex-link-op $n1 $n2 orient right-up
$ns duplex-link-op $n2 $n3 orient right
$ns duplex-link-op $n3 $n4 orient right-up
$ns duplex-link-op $n3 $n5 orient right-down

$ns queue-limit $n2 $n3 2

set tcp [new Agent/TCP]
$ns attach-agent $n0 $tcp
set tsink [new Agent/TCPSink]
$ns attach-agent $n5 $tsink
$ns connect $tcp $tsink
$tcp set fid_ 1

set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ftp set type_ FTP


set udp [new Agent/UDP]
$ns attach-agent $n1 $udp
set usink [new Agent/Null]
$ns attach-agent $n4 $usink
$ns connect $udp $usink
$udp set fid_ 2

set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp
$cbr set packet_size_ 512
$cbr set rate_ 0.05mb
$cbr set type_ CBR

$ns at 0.1 "$cbr start"
$ns at 1.0 "$ftp start"
$ns at 124 "$cbr stop"
$ns at 124.5 "$ftp stop"

$ns at 125 "finish"
$ns run
