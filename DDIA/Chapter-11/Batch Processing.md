
## Batch processing with Unix tools 

batch processing is basically taking a large sized input and producing output, here batch processing is not similar to request/response cycle of a typical web service, a web service is made to return a response whereas our batch processing system does not return any response

The batch job runs periodically throughout the day, example once every hour or once every day.

batch processing algorithms such as MapReduce was the reason why big tech companies like Google in their early time where able to process large amount of user input that it faced using only commodity hardwares (cheap hardwares)

we can simulate a batch processing system using the traditional unix tools such as awk, sort, uniq and others

for example, take the following command:
```
cat /log.txt
```