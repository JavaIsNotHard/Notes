
declarative model and desired state is the core of how kubernetes at the core operate. They work in three basic principles
1. desired state
2. observed state
3. reconciliation 

desired state is what you want, observed state is what you have and reconciliation is how you sync the observed state with the desried state


the declarative model works like this
1. you write a YAML file that describes the desired state for the application
2. you post the YAML to the API server
3. Kubernetes records this in the cluster store as a record of intent 
4. controller's job is to make sure that the observed state matches the desired state
5. the controller reconciles the pod 
6. the controller runs in the background thread

