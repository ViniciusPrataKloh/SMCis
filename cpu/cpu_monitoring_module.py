import os
import sys
import psutil
import time
import datetime
import os.path

#
# CPU rate collector
#
def cpu_rate_collector(p):
    try:
         return p.cpu_percent()
    except Exception as e:
         return 0.00

#
# Memory usage collector
#
def memory_usage_collector(p):
    try:
         return p.memory_percent()
    except Exception as e:
         return 0.00

#
# IO Disk and Network rate collector
#
def io_rate_collector(p, i):
    '''
     Collect before and after to calculate the io rate of disk and network
    '''
    try:
         collected_disk_before = p.io_counters() if p else psutil.disk_io_counters()
         collected_net_before = psutil.net_io_counters(pernic=True)
         time.sleep(0.2)
         collected_disk_after = p.io_counters() if p else psutil.disk_io_counters()
         collected_net_after = psutil.net_io_counters(pernic=True)

         read_per_sec = collected_disk_after.read_bytes - collected_disk_before.read_bytes
         write_per_sec = collected_disk_after.write_bytes - collected_disk_before.write_bytes

         sent_per_sec = collected_net_after[i].bytes_sent - collected_net_before[i].bytes_sent
         recv_per_sec = collected_net_after[i].bytes_recv - collected_net_before[i].bytes_recv

         return {'disk': (read_per_sec, write_per_sec, read_per_sec + write_per_sec), 'net': (sent_per_sec, recv_per_sec, sent_per_sec + recv_per_sec)}
    except Exception as e:
         return {'disk': (0, 0, 0), 'net': (0, 0, 0)}

#
# Instantaneous power collector
#
def power_collector():
    #os.system("/usr/sbin/ipmi-dcmi --get-system-power-statistics | grep Current | awk '{print $4}' >> power.dat")
    os.system("ipmitool dcmi power reading | grep Instantaneous | awk '{print $4}'")
    os.system("./temp.sh")

#
# Writer output data file
#
def output(procname, timestamp, pid, cpu, mem, io):
    out_file = open(procname+".dat", 'a')

    line = []
    line.append(str(timestamp) + "\t")
    line.append(str(pid) + "\t")
    line.append(str(cpu) + "\t")
    line.append(str(mem) + "\t")
    line.append(str(io['disk'][0]) + "\t")
    line.append(str(io['disk'][1]) + "\t")
    line.append(str(io['disk'][2]) + "\t")
    line.append(str(io['net'][0]) + "\t")
    line.append(str(io['net'][1]) + "\t")
    line.append(str(io['net'][2]) + "\n")

    out_file.writelines(line)
    out_file.close()

#
# Writer output json file
#
def output_json(procname, timestamp, cpu, mem, power):
    if os.path.exists("/home/viniciuspk/Documents/Experiments/Monitors/scripts_omp/"+procname+".json"):
        out_file = open(procname+".json", 'a')
        line = []
        line.append("{\"timestamp\":" + str(timestamp) + ", ")
        line.append("\"cpu\":" + str(cpu) + ", ")
        line.append("\"mem\":" + str(mem) + ", ")
        line.append("\"power\":" + str(power) + "},\n")
        out_file.writelines(line)
        out_file.close()
    if not os.path.exists("/home/viniciuspk/Documents/Experiments/Monitors/scripts_omp/"+procname+".json"):
        out_file = open(procname+".json", 'a')
        out_file.writelines("[")
        out_file.close()

#
#  Main function
#
def main():
    PROCNAME = sys.argv[1]
    INTERFACE = sys.argv[2]
    LAUNCHER = "launcher.sh"
    DATE = datetime.datetime.now()
    start = int(DATE.timestamp() * 1000)

    for id in psutil.pids():
         pid = psutil.Process(id)
         if ( pid.name() == LAUNCHER ):
             pid_launcher = pid

    print("Launcher is running with: " + str(pid_launcher))
    while pid_launcher.is_running():
        for pid in psutil.pids():
             proc = psutil.Process(pid)
             if ( proc.name() == PROCNAME ):
                  pid_process = proc
        try:
             print("Monitoring application: " + str(pid_process.name()))
             while pid_process.is_running():
                  cpu = '{:.2f}'.format(cpu_rate_collector(pid_process) / psutil.cpu_count())
                  mem = '{:.2f}'.format(memory_usage_collector(pid_process))
                  io = io_rate_collector(pid_process, INTERFACE)
                  power = power_collector()
                  DATE = datetime.datetime.now()
                  now = int(DATE.timestamp() * 1000)
                  output(PROCNAME, now-start, pid_process.pid, cpu, mem, io)
                  #output_json(PROCNAME, now-start, cpu, mem, str(200))
        except Exception as e:
             power_collector()
             DATE = datetime.datetime.now()
             now = int(DATE.timestamp() * 1000)
             #output_json(PROCNAME, now-start, 0.00, 0.00, str(200))
             output(PROCNAME, now-start, 0, 0.00, 0.00, {'disk': (0, 0, 0), 'net': (0, 0, 0)})
             time.sleep(0.2)

if __name__ == "__main__":
    main()

