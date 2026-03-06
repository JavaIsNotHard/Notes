
how **resolve_timeout** works?
we associate a timer with an alert, every time this alert is send it resets the timer, if this timer reaches the resolve_timeout then it assumes. the alert is resolved and marks it

- **The Firing Signal:** While an alert is active, Prometheus sends a "Firing" message to Alertmanager at every `evaluation_interval` (usually every 15–30 seconds).
    
- **The `EndsAt` Timestamp:** Each message from Prometheus includes a timestamp called `EndsAt`. Prometheus sets this to a few minutes in the future (typically $3 \times \text{evaluation\_interval}$).
    
- **The Reset:** Every time Alertmanager gets a fresh update, it pushes that `EndsAt` deadline further back.
    
- **The Silence:** If Prometheus stops sending updates (maybe the network cut out or the server crashed), Alertmanager waits until the `EndsAt` time passes.
    
- **The Auto-Resolve:** Once that timer hits zero, Alertmanager says, _"I haven't heard about this problem in a while, so I'll assume it's fixed,"_ and it marks the alert as **Resolved**.