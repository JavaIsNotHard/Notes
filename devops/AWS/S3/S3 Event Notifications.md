helps to triggers notification based on events happening in s3
s3 events include
- `s3:ObjectCreated:` — any upload
- `s3:ObjectRemoved:` — any delete
- `s3:ObjectRestore:` — Glacier restores
- `s3:Replication:` — replication failures

![[Pasted image 20260306135957.png|292]]

for this to work, we need to configure resource based permissions to the destination side

![[Pasted image 20260306140811.png]]


instead of sending the events directly to the services, we can instead send it first to the Amazon EventBridge which can send events to 18 different aws services through filtering

using this, we can send events to different destination at a time