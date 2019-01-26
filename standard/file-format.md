## makeSharp Profile Format

---

```json
{
    "name": "hello",
    "version": "1.0.0",
    "author": "Alan Turing",
    "description": "A creative package",
    "repository": "https://example.com/repos/hello",
    "script": {
        "test-main": "hello name"
    },
    "denpendencies": {
        "runtime": [
            "third_party/json",
            "third_party/true_type"
        ],
        "static": [
            "third_party/csv",
            "third_party/mpl"
        ]
    },
    "dest": {
        "include": ["include", "test/include"],
        "source": ["src", "test"]
    },
    "target": [
        {
            "type": "shared",
            "directory": "bin"
        },
        {
            "type": "executable",
            "directory": "test"
        }
    ],
    "license": "GPL-v2"
}
```

