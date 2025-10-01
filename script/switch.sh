#!/bin/bash
a=${1:?a}
b=${2:?b}
op=${3:?op}

case $op in
    +) echo "Result: $((a + b))" ;;
    -) echo "Result: $((a - b))" ;;
    \*) echo "Result: $((a * b))" ;;
    /) echo "Result: $((a / b))" ;;
    *) echo "Invalid Operation" ;;
esac

