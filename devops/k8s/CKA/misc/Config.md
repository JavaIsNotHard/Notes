# View current context
kubectl config current-context

# List all contexts
`kubectl config get-contexts`

# Switch to a different context
`kubectl config use-context <context-name>`

# Set default namespace for current context
`kubectl config set-context --current --namespace=<namespace>`

# Create a new context
`kubectl config set-context <context-name> --cluster=<cluster> --user=<user> --namespace=<namespace>`

# Delete a context
`kubectl config delete-context <context-name>`

# Rename a context
`kubectl config rename-context <old-name> <new-name>`




Imagine you're a DevOps engineer working with:

- A local development cluster (Minikube)
- A staging cluster (EKS on AWS)
- A production cluster (GKE on Google Cloud)

# Development
kubectl config set-context dev --cluster=minikube --user=minikube --namespace=dev

# Staging
kubectl config set-context staging --cluster=eks-staging --user=staging-admin --namespace=staging

# Production
kubectl config set-context prod --cluster=gke-prod --user=prod-admin --namespace=production

```
kubectl config use-context dev     # Work on development
kubectl config use-context staging # Test in staging
kubectl config use-context prod    # Deploy to production
```

