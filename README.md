# Requirement
- python2.7
- boost.python
# Installation
```
cmake . -DCMAKE_CXX_COMPILER=g++
make  
```
# Instruction
```
import sklearn.datasets  
from libclustering import pam  
obj = pam(2)  
data = sklearn.datasets.load_wine()['data']  
clusters = obj.fit(data.tolist())
```
- The python list named "clusters" has cluster information.
