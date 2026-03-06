instead of the bucket owner paying for storage and network cost of the bucket when a requester downloads files from the bucket, we instead let the requester pay for the network cost when downloading the file

this is mainly used when sharing large dataset between separate AWS accounts
which means the requester must have an authenticated AWS account and the price to download the file is transferred to the requester's bill instead of the bucket owner

