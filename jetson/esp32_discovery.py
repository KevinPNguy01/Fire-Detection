from zeroconf import Zeroconf, ServiceBrowser
import time

class Listener:
    def __init__(self):
        self.ip = None

    def add_service(self, zeroconf, type, name):
        info = zeroconf.get_service_info(type, name)
        if info and b'esp32' in info.name.encode():
            self.ip = ".".join(map(str, info.addresses[0]))

    def remove_service(self, zeroconf, type, name): 
        pass

    def update_service(self, zeroconf, type, name): 
        pass


def find_esp32() -> str | None:  
    """
    Discover the ESP32 device on the local network using Zeroconf.

    Returns:
        str or None: The IP address of the ESP32 device if found, otherwise None.
    """

    print("Searching for ESP32...")
    zeroconf = Zeroconf()
    listener = Listener()
    browser = ServiceBrowser(zeroconf, "_http._tcp.local.", listener)
    timeout = time.time() + 5
    while listener.ip is None and time.time() < timeout:
        time.sleep(0.1)
    zeroconf.close()
    return listener.ip