#!/usr/bin/env bash
#===============================================================================
# Script Name   : example.sh
# Description   : Template for safe, maintainable shell scripts
# Author        : Your Name
# Date          : 2025-09-30
#===============================================================================

# --- Strict modes (safety first) ---
set -euo pipefail
IFS=$'\n\t'

# --- Globals ---
SCRIPT_NAME=$(basename "$0")
LOG_FILE="/tmp/${SCRIPT_NAME}.log"

# --- Logging functions ---
log_info()  { echo "[INFO]    $*" | tee -a "$LOG_FILE" >&2; }
log_warn()  { echo "[WARNING] $*" | tee -a "$LOG_FILE" >&2; }
log_error() { echo "[ERROR]   $*" | tee -a "$LOG_FILE" >&2; }
log_debug() { [[ "${DEBUG:-0}" -eq 1 ]] && echo "[DEBUG]   $*" | tee -a "$LOG_FILE" >&2; }

# --- Cleanup trap (runs on exit) ---
cleanup() {
    log_debug "Cleaning up temporary files..."
    # Example: rm -f "$TMP_FILE"
}
trap cleanup EXIT

# --- Usage/help function ---
usage() {
    cat <<EOF
Usage: $SCRIPT_NAME [options]

Options:
  -f <file>    Input file (required)
  -n <num>     Number of iterations (default: 1)
  -h           Show this help

Example:
  $SCRIPT_NAME -f data.txt -n 5
EOF
    exit 1
}

# --- Parse arguments ---
FILE=""
NUM=1

while getopts ":f:n:h" opt; do
    case $opt in
        f) FILE=$OPTARG ;;
        n) NUM=$OPTARG ;;
        h) usage ;;
        :) log_error "Option -$OPTARG requires an argument."; usage ;;
        \?) log_error "Invalid option: -$OPTARG"; usage ;;
    esac
done

shift $((OPTIND-1))

# --- Validate inputs ---
if [[ -z "$FILE" ]]; then
    log_error "Missing required argument: -f <file>"
    usage
fi
if [[ ! -f "$FILE" ]]; then
    log_error "File not found: $FILE"
    exit 1
fi
if ! [[ "$NUM" =~ ^[0-9]+$ ]]; then
    log_error "NUM must be an integer"
    exit 1
fi

# --- Main logic ---
main() {
    log_info "Starting script..."
    log_info "Processing file: $FILE, iterations: $NUM"

    for ((i=1; i<=NUM; i++)); do
        log_debug "Iteration $i"
        # Example task
        line_count=$(wc -l < "$FILE")
        log_info "Line count: $line_count"
    done

    log_info "Done."
}

main "$@"

