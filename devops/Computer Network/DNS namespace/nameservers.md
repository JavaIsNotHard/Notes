portion of the domain namespace is assigned to individuals or organizations

ICANN oversees the root, Verisign manages .com domain

registry vs registrar


contains a stub-resolver which is a software component that is found in all host machines that is connected to the internet, whose job is basically to send dns queries over the network 

1. You type `www.google.com` in the browser.
2. The browser uses OS DNS APIs (e.g., `getaddrinfo()`).
3. The stub resolver reads DNS server IP from config.
4. It sends a UDP request to `8.8.8.8`.
5. That DNS server recursively resolves the domain and replies with the IP.
6. The stub resolver caches it and returns it to your app.

