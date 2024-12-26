if [ -z "$1" ]; then
    echo "Usage: $0 <pid>"
    exit 1
fi

PID=$1
ITERATIONS=1000

for ((i=1; i<=ITERATIONS; i++))
do
    MESSAGE="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"
    ./client "$PID" "$MESSAGE"
done

