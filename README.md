# diskcopy
Utility like ddrescue to read floppy disks into a virtual disk image. Unlike ddrescue, the user has more control over error cases, which will hopefully not break the floppy drive.

# Build
```
make
```

This produces a diskcopy binary under the out/ directory.

## Run Unit Tests

```
make unittest
```