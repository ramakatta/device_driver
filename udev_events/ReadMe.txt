1. Insert kernel module
2. Observe the events
   udevadm monitor --kernel --property 
3. create file : /etc/udev/rules.d/99-uevent.rules
# udev rule for mychardev uevents
KERNEL=="uevent_sender", ACTION=="change", ENV{CUSTOM_EVENT}=="1", RUN+="/bin/bash /usr/local/bin/handle_uevent.sh"
4. create
/usr/local/bin/handle_uevent.sh
#!/bin/bash

# Udev handler script to be executed when the custom uevent is received.
#
# Udev passes various environment variables, including:
# DEVPATH: The kernel device path.
# ACTION: The action that triggered the event (e.g., 'add', 'remove', 'change').
# Plus our custom variable:
# CUSTOM_EVENT: "1"

LOG_FILE="/tmp/custom_uevent_log.txt"

# Add a timestamp and the main environment variables to the log file
echo "--- $(date '+%Y-%m-%d %H:%M:%S') ---" >> "$LOG_FILE"
echo "Uevent Received!" >> "$LOG_FILE"
echo "ACTION: $ACTION" >> "$LOG_FILE"
echo "DEVPATH: $DEVPATH" >> "$LOG_FILE"
echo "CUSTOM_EVENT: $CUSTOM_EVENT" >> "$LOG_FILE"

# Log all environment variables provided by udev (for debugging)
echo "--- All Udev Environment Variables ---" >> "$LOG_FILE"
env >> "$LOG_FILE"
echo "-------------------------------------" >> "$LOG_FILE"

# NOTE: udev executes scripts very quickly. Avoid long-running processes here.
# For complex tasks, this script should launch a separate background process.

exit 0
5.  Run these commands
sudo udevadm control --reload-rules
sudo udevadm trigger
6. Observe the log
 /tmp/custom_uevent_log.txt
