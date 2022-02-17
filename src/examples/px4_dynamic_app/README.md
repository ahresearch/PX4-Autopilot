# PX4 dynamic applicatioin

This is an app that can be dynamically loaded

### Building
```
Build the attack dynamic module.

make px4_sitl

This will create build/px4_sitl_default/src/examples/px4_dynamic_app/examples__px4_dynamic_app.px4mod

Copy examples__px4_dynamic_app.px4mod as px4-dynamic_app.px4mod in folder build/px4_sitl_default/tmp/rootfs

Run px4:  
make px4_sitl jmavsim  
At the px4 prompt type 'dyn px4_dynamic_app.px4mod'  
This will start the application.
```
