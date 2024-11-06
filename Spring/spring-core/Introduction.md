What is spring? 
Spring works in the principle of inversion of conversion which means that control of programs are not in the hand of the programs but rather are given to some external container or manager. In case of spring, it would be the spring application context. 

dependency injection container which is handled by spring application context. 

The container manages the creation and deletion of objects or beans that are defined through the configuration of the project 

There are two main ways to write spring configuration
1. XML based 
2. Java based 
3. Annotation based 
Annotation based using the `@Configuration` annotation is the most used approach where we register the configuration class in the application context 

We can have multiple configuration class so wee need to make sure that we differentiate between these classes properly.
We can define one configuration file in another using the `@Import` annotation. 

Configuration classes consists of beans. Beans are annotated using `@Bean` and basically are methods inside the classes which perform some functionality. Beans are also spring components hence are instantiated during the creation of the application context. If the bean has a certain dependency then we do not have to manually inject that dependency. The spring container will search for the corresponding dependency and inject that i.e create and object instance with that dependency. 

Spring also has something called as component scanning which basically scans all the file in the classpath to find all the beans that components that are defined and have to be instantiated for the application to run properly 

How beans are constructed are defined by the scope of the bean 
1. singleton -> your component will be initialized once and then will be cached int he application context for future use. 
	```java
@Bean 
public AccountService accountService() {
	return ...
}

@Bean 
@Scope("singleton")
public AccountService accountService() {
	return ...
}
```
	These two are the same things. 
	```java 
AccountService service1 = (AccountService) context.getBean("accountService");
AccountService service2 = (AccountService) context.getBean("accountService");

assertEqual(serivce1 == service2);
```
	The result in true because both `service1` and `service2` access the same `AccountService` bean. This means that singleton scope only creates a single instance of the bean throughout the application. 
	Disadvantages:
	- Race condition
	
2.  protocol -> A new bean is going to be constructed each time it is accessed through the spring application context. 

	```java
@Bean
@Scope("protocol")
public AccountService accountService() {
	return ...
}
```

	```java
AccountService service1 = (AccountService) context.getBean("accountService");
AccountService service2 = (AccountService) context.getBean("accountService");

assertEqual(serivce1 != service2);
```
	This also yields the result true because `service1` and `service2` references different bean as opposed to the singleton scope.

3.  Session 
4. Request
5. Websocket
6. Custom

Component don't need to find their dependecies, the container will inject it for them. 


Java  based configuration -> configuration where independent of our business logic. they were decoupled 
Annotation based configuration  ->  
use of `@Component` annotation to specify that it is a spring managed bean 
configuration that is embedded in our business classes 
needs component scanning to find any classes annotated with `@Component` , when found this class will be initalized and made part of the application context 

Dependency injection in annotation 
- autowired
	- constructor injection -> constructor marked with `@Autowired` will inject any argument that we define in the constructor. If we have a single constructor then we do not need to add the `@Autowired` annotation.
	- Method injection -> works in  method layer 
	- Field injection  -> discouraged, annotation are processed by the framework , if you are on your own without the framework like in unit test then the `@Autowired` annotation will not be processed and there will not be any way to pass this dependency 
- it is required for the dependency to be in the application context, can be changed using the `@Autowired(required=false)` annotation
- **Autowiring ambiguity** `@Autowired` is doing autowiring by type that means, we go to the application context and find something by type 
	- using autowiring by name and `@Qualifier` annotation 


Java based component vs annotation based component 
@Bean vs @Component annotation





## Inside the spring container 
1. Initialization 
2. Usage 
3. Destruction 


### The initialization phase 
happens when we call the 
`ApplicationContext context = SpringApplication.run(AppConfig.class)`

what happens when we call the run methods
 - load and process bean definition
 - perform bean initialization 
 - find dependencies for each bean and create them 
- Add every bean definition in the bean factory
- The `BeanFactoryPostProcessor` bean is invoked 
- the bean factory is mapping between a bean id and a bean definition, the bean factory is inside the memory 
- Post process bean factory -> can modify the definitibon of any bean in the factory before the object is created 
 - This is an extension point that we have in the container 
 - we can implement our own bean post processor, the `BeanFactoryPostProcessor` is a functional interface (what is this) that has a single method called `postProcessBeanFactory`. In this point in time the beans have not been instantiated yet 
 - An example of the `postProcessBeanFactory` is the `propertySourcePlaceholderConfigurer` which is a builtin bean post processor which replaces variables with external values 
 - We  can also define our own bean post processor by implementing the `BeanFactoryPostProcessor` interface .

### Bean Creation 
determining the dependency of the component 
each singleton bean early initialized to make sure that there are not errors and fail fast. 
we can also mark the bean as lazy to construct the bean later
Post processing phase and then the beans are ready to use 
In the post processing phase of the bean, here we are calling the `@PostConstruct` methods or init-method 
This is a extension point which means that it can modify any bean defined in the application context 
the `BeanPostProcessor` is different from `BeanFactoryPostProcessor` in the sense that the latter happens before the initialization and the former happens after the initialization. 
This interface has two methods which include `postProcessBeforeInitalization` and `postProcessAfterInitialization`  

### Bean destruction
- All the `@PreDestroy` methods are invoked
- All the beans are made available for garbage collection 
- This also happens when a bean goes out of scope. This only apples for beans that have scope except the `protocol` scope because we do not know that. 
- The destruction only happens when the application is gracefully shut down and not killed 


### Bean ordering 
- We can use the `@dependsOn` annotation to explicitly define the dependency of the bean either in the class level or method level. 



# Aspect oriented programming in spring 
### What problem does AOP solve?
- modularization of cross-cutting concerns 

What is a cross cutting concern? 
Cross cutting concern is a behavior that spans across the codebase, so basically you will have the same behavior among multiple classes in the same codebase 
Example
Perform a role base security check before every application method 
here the every keyword in the requirement is a sign that it required modularization 

What if we do not modularize cross-cutting concerns 
- code tangling  -> having code that is not of this domain, for example if we have a security check in every application method then we will have security along with business logic so if we want to test this business logic then we need to provide it with the security somehow. mixing of concerns, we have a lot of stuff done in the same component 
- code scattering  -> Same security check in all methods and classes 

Things to remember about AOP
- the concerns with be separate i.e the method should only contain the business logic 
- the aspect that performs operation other than the business logic should be placed in its own container or class.
- Then we weave this two together to get our desired outcome


### What are core AOP concepts 
- join point  -> point of execution in our application, method call, exception thrown. 
- Pointcut -> expression that is going to be in the form of aspectJ language. will select one or more join point where we are going to execute our piece of code. At which point should the aspect to applied 
-  advice -> the code that we want to execute. The security checker can be the advice . Action taken by the aspect at a particular join point 
- aspect -> encapsulates the what and the where, encapsulates pointcuts and advice.
- weaving -> apply aspects in our main application code. 

```java
package com.package.jibesh;

@Aspect 
public class LoggingAspect { 
	// point cut
	@Pointcut("execution(* com.example.service.*.*(..))") 
	private void selectAllMethods() {}

	// aspect 
	@Before("selectAllMethods()") public void beforeAdvice() { System.out.println("A method is about to be executed."); } 

	// aspect
	@After("selectAllMethods()") public void afterAdvice() { System.out.println("A method has just executed."); } }
```

Here join point are all the methods in the `com.package.jibesh` package 

Consider a basic requirement
log a message every time a property is about to change 

![[Screenshot from 2024-07-18 12-46-44.png]]
This is a overview of how aspect are applied during the spring runtime 

Advice types: 





# Transactions in spring 
