# Path Tracing

TODO:
* Measure in home machine
* https://jacco.ompf2.com/2022/04/18/how-to-build-a-bvh-part-2-faster-rays/ 
  Low hanging fruit
* TODO: add signposts and learn how to profile with instrument

## Performance
Apple M2 Max
```
+----------------------+---------+---------+---------+
| Experiment           | BVH     | Tracing | Mrays/s |
+----------------------+---------+---------+---------+
| Unordered SAH        | 3635 ms |   90 ms |  4.5511 |
| Ordererd + Stackless | 3435 ms |  125 ms |  3.2768 | <-- SLOWER!!!
+----------------------+---------+---------+---------+
```

## Logs
Jul 31, 2024:
* Fixed assert when evaluating SAH, note that 0 * inf = nan (expected).
* Fixed bug in stackless traversal 
