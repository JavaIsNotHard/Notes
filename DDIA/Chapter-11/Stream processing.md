- batch processing jobs happen in a certain interval, for example, between every 10 seconds or every 10 minutes or every day
- In batch processing, input is bounded i.e the input size in known and is of finite size which means the batch job knowns when the job completes 

- in reality, there are a lot of unbounded inputs i.e they are generated continuously over time 
- this kind of input includes for example, user buying stuff from your platform, the user are going to keep buying stuff until the service is closed
- in batch processing, input for a job must be of fixed size, so the user input must be between a certain time duration for those inputs to be processed

- batch processing has the overhead of waiting for the result which can be solved by simply processing each input or event as they arrive in the system

- stream means data is made incrementally available over time 
- in batch processing system, the input for processing are sequence of bytes or files whereas in stream processing it is known as an [[event]]