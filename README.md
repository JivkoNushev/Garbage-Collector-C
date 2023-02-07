# Garbage-Collector-C

## A simple implementation of a garbage collector in C using two Lists:
-   First: stores allocated memory addresses
-   Second: stores created pointers

## The idea is to keep track of the memory pointed by the pointers, and when an allocated memory isn't pointed at anymore, to free it