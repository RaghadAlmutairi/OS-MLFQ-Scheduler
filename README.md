
# Multilevel Feedback Queue (MLFQ) CPU Scheduler  
### Operating Systems Course Project (2023)

This repository contains a complete implementation of a **Multilevel Feedback Queue (MLFQ)** scheduler written in C.

---

## 📌 Repository Name
OS-MLFQ-Scheduler

## 📄 Project Description
An Operating Systems course project implementing a three‑level CPU scheduler:
- Q0 → Round Robin (Quantum = 8)
- Q1 → Round Robin (Quantum = 16)
- Q2 → FCFS

Metrics calculated:
- Waiting Time
- Response Time
- Turnaround Time
- Average Waiting Time
- Throughput

---

## 🧠 Scheduling Flow Diagram (Text-Based)

```
          ┌──────────────┐
          │   New PCB    │
          └──────┬───────┘
                 │ Arrival
                 ▼
      ┌─────────────────────────┐
      │   Q0: RR (Quantum = 8)  │
      └───────────┬─────────────┘
                  │ If not finished
                  ▼
      ┌─────────────────────────┐
      │  Q1: RR (Quantum = 16)  │
      └───────────┬─────────────┘
                  │ If not finished
                  ▼
      ┌─────────────────────────┐
      │      Q2: FCFS Queue     │
      └───────────┬─────────────┘
                  │ Finish
                  ▼
          ┌──────────────┐
          │ Terminated    │
          └──────────────┘
```

---

## ▶️ How to Compile & Run

### Compile:
```bash
gcc scheduler.c -o scheduler
```

### Run:
```bash
./scheduler
```


