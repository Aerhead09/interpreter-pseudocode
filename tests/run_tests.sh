#!/bin/bash

PASS=0
FAIL=0
TOTAL=0

if [ ! -f "../bin/interpreter" ]; then
    echo "[ERROR] Binary tidak ditemukan di ../bin/interpreter"
    exit 1
fi

for f in cases/*.psdc; do
    name=$(basename "$f" .psdc)
    src="cases/$name.psdc"
    expected="cases/$name.expected"
    input="cases/$name.in"
    out="output_$name.txt"

    TOTAL=$((TOTAL + 1))

    if [ -f "$input" ]; then
        ../bin/interpreter "$src" < "$input" > "$out" 2>/dev/null
    else
        ../bin/interpreter "$src" < /dev/null > "$out" 2>/dev/null
    fi

    if [ -f "$expected" ]; then
        if diff -q "$out" "$expected" > /dev/null; then
            echo "[PASS] $name"
            PASS=$((PASS + 1))
        else
            echo "[FAIL] $name"
            FAIL=$((FAIL + 1))
        fi
    else
        echo "[SKIP] $name (no expected)"
    fi
done

echo ""
echo "================================"
echo "Total: $TOTAL  Pass: $PASS  Fail: $FAIL"
echo "================================"

if [ $FAIL -gt 0 ]; then
    exit 1
fi