observability
Observability lets you understand a system from the outside by letting you ask questions about that system without knowing its inner workings.


To ask those questions about your system, your application must be properly instrumented.

That is, the application code must emit [signals](https://opentelemetry.io/docs/concepts/signals/) such as [traces](https://opentelemetry.io/docs/concepts/signals/traces/), [metrics](https://opentelemetry.io/docs/concepts/signals/metrics/), and [logs](https://opentelemetry.io/docs/concepts/signals/logs/)
SLI (service level indicator) -> a measurement of how your system is performing.
Area -> SLI (measurement)
Availability -> 99.9% of requests return HTTP 200
Latency -> 95% of requests complete under 200ms
Error rate -> < 0.1% error responses
Durability -> % of data that is not lost
Throughput -> Requests per second

SLO (service level objective) -> a target for the SLI, what level do you wish to perform at
- _Availability SLO:_ **99.9% uptime per month**
- _Latency SLO:_ **95% of API calls under 300ms**
- _Error rate SLO:_ **99.5% success rate**
- _Durability SLO:_ **99.999999% data durability** (S3 style)

If your SLI falls below the SLO → **you are breaking your reliability promise**.

Span -> A **span** represents a **single operation or unit of work** in your system.
It captures:
- **Start time**
- **End time**
- **Duration**
- **Metadata (tags, logs, attributes)**

Spans are used to build a **trace**, which represents the **entire journey of a request** through your system.

spans together form a trace which shows the full path the request took


demo -> grpc  -> otel collector (receiver + processor + exporter) -> otel collector 
demo -> http POST