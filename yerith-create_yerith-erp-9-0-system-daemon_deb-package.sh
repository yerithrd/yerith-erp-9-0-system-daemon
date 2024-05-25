#!/bin/bash

rm -f yerith-erp-9-0-system-daemon.deb

cp bin/yerith-erp-9-0-system-daemon yerith-erp-9-0-system-daemon/opt/yerith-erp-9-0-system-daemon/bin

chmod go+rw yerith-erp-9-0-system-daemon/opt/yerith-erp-9-0-system-daemon/yerith-erp-9-0-system-daemon.log

chmod 755 yerith-erp-9-0-system-daemon/DEBIAN/postinst

dpkg-deb --build yerith-erp-9-0-system-daemon
