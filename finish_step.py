import urllib.request
try:
    urllib.request.urlopen("http://localhost:11434/api/generate", timeout=1)
except Exception:
    pass
print("Completed step")
