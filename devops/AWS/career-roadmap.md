# AWS → Distributed Systems Engineer L5 Roadmap

Target role: **Distributed Systems Engineer 5 — Cloud Platform Infrastructure Engineering**.
Current baseline: AWS Solutions Architect study, multiple sources.

> SAA cert ≠ role. Cert teaches service selection. Role demands platform building, control-plane design, p99.9 debugging, multi-region failover at 3am.

---

## 1. Gap Map

### Distributed systems fundamentals (non-AWS)
- MIT 6.824 lectures (YouTube, free). Raft, Paxos, MapReduce, Spanner.
- **Designing Data-Intensive Applications** (Kleppmann) — required reading.
- Papers: Dynamo, Bigtable, Chubby, Borg, Aurora, S3 strong-consistency, FoundationDB, Dapper, Tail at Scale.

### AWS depth beyond SAA
- Path: SAA → SAP (Solutions Architect Pro) → **Advanced Networking Specialty**.
- Networking specialty screens for infra roles.
- Hands-on: multi-account org, Transit Gateway, PrivateLink, hybrid VPN/Direct Connect, IPv6 dual-stack.
- Read every article on **AWS Builder's Library** (builder.aws.com).

### IaC + platform primitives
- Terraform (required). CDK (nice). Pulumi (optional).
- Reusable modules, state backend, drift detection, policy-as-code (OPA/Sentinel).
- Kubernetes (EKS): pod networking, CNI, CoreDNS, controllers/operators. Write a Go controller.

### Production skills
- Linux internals: namespaces, cgroups, eBPF, tcpdump, strace, perf.
- Observability: Prometheus, OpenTelemetry, distributed tracing, SLO/SLI math, error budgets.
- Incident response: runbooks, postmortems, blast-radius thinking.

### Code
- Pick **Go** or **Rust**. Infra roles write tools, controllers, agents. Python alone insufficient at L5.

---

## 2. Project Ladder

1. Multi-account AWS org via Terraform + SCPs + Control Tower.
2. EKS cluster with Karpenter autoscaling, ArgoCD, Istio/Linkerd, observability stack.
3. Kubernetes operator that reconciles AWS resource (e.g. RDS via ACK).
4. Multi-region active-active: Route53 + DynamoDB Global Tables. Prove RTO/RPO via chaos test.
5. Internal developer platform: Backstage + Crossplane.

---

## 3. Interview Prep (L5)

- **System design**: design S3, DynamoDB, Lambda cold-start path, multi-region database.
- **Behavioral**: STAR stories on incidents, scale, ambiguity, cross-team influence.
- **Coding**: not LeetCode-hard — concurrency, rate limiter, LRU, consistent hashing.

---

## 4. Performance Engineering Track

Why: L5 cloud infra eng must debug noisy neighbor, p99 spike, kernel stall, NUMA, network microbursts. "Restart pod" not an answer.

### Gregg canon
- **Systems Performance**, 2nd ed (2020) — bible.
- **BPF Performance Tools** (2019) — bcc/bpftrace.
- brendangregg.com — flame graphs, USE method, perf checklist.
- Netflix talks on YouTube: "Linux Performance Tools", "Container Performance Analysis".

### Mental models
- **USE method**: Utilization, Saturation, Errors per resource.
- **RED method**: Rate, Errors, Duration per service.
- Workload characterization before optimization. Measure, don't guess.
- Latency heatmaps > averages. p50 lies, p99.9 tells truth.

### Skill stack
1. Linux internals: CFS scheduler, page cache, THP, NUMA, block I/O, TCP tunables.
2. Tools: `perf`, `bpftrace`, `bcc` (`execsnoop`, `biolatency`, `tcpconnect`), `ftrace`, eBPF.
3. Flame graphs: CPU, off-CPU, memory, syscall.
4. Benchmarking: `fio`, `wrk`, `iperf3`, `sysbench`.
5. Runtime perf: GC tuning, escape analysis, `pprof`.

### AWS-flavored perf
- EC2 internals: Nitro, ENA driver, EBS-optimized, placement groups, SR-IOV.
- Network: PPS limits, ENA queue depth, jumbo frames, cluster placement.
- Storage: gp3 vs io2, IOPS vs throughput, EBS burst credits, instance store NVMe.
- Lambda cold start, Firecracker microVM.
- AWS re:Invent perf deep-dives (CMP, NET tracks).

---

## 5. 90-Day Perf Curriculum

Assumes 10–12 hrs/week. Linux box + AWS account.

### Prereqs (week 0)
- Ubuntu 22.04 VM or EC2 (`m5.large` min, `c5.xlarge` better). Root access.
- Install: `linux-tools-generic`, `bpfcc-tools`, `bpftrace`, `sysstat`, `iotop`, `htop`, `perf`, FlameGraph scripts, `fio`, `wrk`, `iperf3`, `stress-ng`.
- Clone: `github.com/brendangregg/FlameGraph`, `github.com/iovisor/bcc`, `github.com/iovisor/bpftrace`.
- Books: *Systems Performance 2e*, *BPF Performance Tools*.

### Month 1 — Foundations + CPU
- **Week 1**: SysPerf ch.1-2. USE, RED, workload characterization. USE-checklist via `top`, `vmstat`, `iostat`, `mpstat`, `sar`. Deliverable: USE report idle vs `stress-ng --cpu 4`.
- **Week 2**: SysPerf ch.6. CFS scheduler, run queue, context switch, NUMA, CPU caches, IPC. Tools: `perf stat`, `perf top`, `pidstat`, `turbostat`. Deliverable: IPC drop writeup.
- **Week 3**: Flame graphs. brendangregg.com/flamegraphs.html. `perf record -F 99 -g`, `stackcollapse-perf.pl`, `flamegraph.pl`. Deliverable: 3 annotated flame graphs (Nginx, Go HTTP under `wrk`, Python).
- **Week 4**: Off-CPU + scheduler. Tools: `bpftrace`, `offcputime-bpfcc`, `runqlat-bpfcc`, `cpudist-bpfcc`. Deliverable: off-CPU flame graph + finding.

### Month 2 — Memory, I/O, Networking
- **Week 5**: Memory. SysPerf ch.7. Virtual memory, page cache, swap, THP, NUMA, OOM. Tools: `free`, `vmstat`, `/proc/meminfo`, `numastat`, `slabtop`, `pmap`. Deliverable: memory USE + NUMA experiment (`numactl --membind`).
- **Week 6**: Disk I/O + filesystems. SysPerf ch.8-9. Tools: `iostat -xz 1`, `biolatency-bpfcc`, `biosnoop-bpfcc`, `fio`. Deliverable: EBS gp3 vs io2 perf characterization.
- **Week 7**: Host networking. SysPerf ch.10. Cloudflare Linux network stack series (Majkowski). Tools: `ss -i`, `tcpdump`, `tcpretrans-bpfcc`, `tcplife-bpfcc`, `nstat`, `ethtool -S`. Tune `net.core.rmem_max`, `tcp_congestion_control` (bbr vs cubic). Deliverable: tuning before/after.
- **Week 8**: eBPF + bpftrace. *BPF Performance Tools* ch.1-5. Deliverable: custom `.bt` script tracing syscall latency for target PID.

### Month 3 — AWS + Interview-Grade Depth
- **Week 9**: EC2/Nitro internals. AWS Nitro whitepaper, ENA docs, re:Invent NET402 + CMP404. Topics: PPS limits, ENA queues, placement groups, SR-IOV. Deliverable: PPS scaling chart `c5n.large` vs `c5n.4xlarge` with bottleneck root cause via `ethtool -S | grep -i drop`.
- **Week 10**: Containers + K8s perf. Gregg "Container Performance Analysis". cgroup v2 docs. Tools: cgroup interfaces, `crictl`, `kubectl top`, `pprof`. Deliverable: incident writeup "p99 spiked after node packing increase".
- **Week 11**: Distributed perf — tracing + tail latency. Dean & Barroso "Tail at Scale", Dapper paper, OpenTelemetry spec. Tools: Jaeger/Tempo + OTel, Prometheus histograms, `histogram_quantile`. Deliverable: tail latency analysis with proper p50/p99/p999 math.
- **Week 12**: Capstone. 3-tier app on AWS (ALB → ECS/EKS → RDS). Load with `k6` or `wrk`. Inject 3 bugs: lock contention, slow query (no index), undersized ENI. Investigate via perf tools only. Deliverable: full investigation report — USE/RED, flame graphs, bpftrace, root cause, fix, before/after.

### Habits
- 1 paper/week. Start: Dean "Numbers Every Programmer Should Know", Tail at Scale, Dapper, Aurora, FoundationDB.
- 1 Gregg blog post/week.
- Push all writeups to public GitHub — interview signal.

### Exit criteria (post-90 days)
- USE method on any Linux box in 10 min.
- Generate + read CPU/off-CPU flame graph unaided.
- Write custom `bpftrace` script for unknown bug.
- Explain p99 vs p99.9 math, why averages lie.
- 1 public capstone investigation.

---

## 6. Overall Pacing

12–18 months realistic from mid-level. Parallel tracks:
- SAA: 1–2 months
- SAP: month 3
- Networking Specialty: month 5
- Perf 90-day: months 4–6
- Projects 1–5: continuous
- 1 paper/week throughout

After 90-day perf → revisit DDIA → Advanced Networking specialty → L5 system design prep.

---

## 7. Key Resources

| Type | Resource |
|------|----------|
| Book | Designing Data-Intensive Applications — Kleppmann |
| Book | Systems Performance 2e — Gregg |
| Book | BPF Performance Tools — Gregg |
| Course | MIT 6.824 (YouTube) |
| Site | builder.aws.com (AWS Builder's Library) |
| Site | brendangregg.com |
| Repo | github.com/brendangregg/FlameGraph |
| Repo | github.com/iovisor/bcc |
| Repo | github.com/iovisor/bpftrace |
| Papers | Dynamo, Bigtable, Chubby, Borg, Aurora, S3, Dapper, Tail at Scale, FoundationDB |
