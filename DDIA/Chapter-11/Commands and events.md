event sourcing makes distinction between commands and events 
when the user request first arrives then it is a command, a command can fail if it doesn't maintain some integrity or constraint that is enforced to it, if it is invalid then it is rejected, if the command is valid then it becomes an event which is durable and immutable 

the process of validation and publishing the event to a broker can be wrapped around a transaction such that it provides the atomicity guarantee that if one of the two fails then the both of them fail at the same time and there are not inconsistency between them 

example, if a user registers a username, then the validation could be to check if the username is already taken or not, if the validation is successful then the application generates an event 

command represents the future -> represents a desire to act or asks to perform an action
event represents the past -> represents what already has happened or represents records that an action has occurred 

we can either validate the request synchronously or asynchronously
when validation synchronously, the command validation must happen before the event is emitted to the consumer whereas in asynchronously validation, we first emit a tentative event and return a response back to the user telling that the was processed and then run a background process to validate the request, if the validation is successful then emit another event telling that the validation was successful else emit an event telling the validation failed 

emitting an event means writing the event on a durable append-only log like eventstore or the log used by apache kafka 

events, once generated are also called facts, suppose the customer wants to remove their username from the site but the event that they registered the username still persists in the log, another event requesting to remove the username from the site is added to the log