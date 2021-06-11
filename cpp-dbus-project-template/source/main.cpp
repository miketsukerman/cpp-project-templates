#include <spdlog/spdlog.h>
#include <dbus/dbus.h>

#include "sample.h"

// using DBusConnectionUPtr = std::unique_ptr<DBusConnection>;

struct DBusVersion {
    int major = 0;
    int minor = 0;
    int patch = 0;
};

int main(int argc, char **argv) 
{
    spdlog::info("Starting server");

    DBusConnection* dbus_conn = nullptr;
    DBusError dbus_error;
    DBusVersion dbus_version;

    // Initialize D-Bus error
    ::dbus_error_init(&dbus_error);

    // D-Bus version
    dbus_get_version(&dbus_version.major, &dbus_version.minor, &dbus_version.patch);
    spdlog::info("DBus version: {}.{}.{}", dbus_version.major, dbus_version.minor, dbus_version.patch);

    // Connect to D-Bus
    spdlog::info("Connecting to the system bus: {}", DBUS_BUS_SYSTEM);
    dbus_conn = ::dbus_bus_get(DBUS_BUS_SYSTEM, &dbus_error);

    if(dbus_conn) {
        spdlog::info("Connected to D-Bus as {}", ::dbus_bus_get_unique_name(dbus_conn));
        return 0;
    }

    spdlog::error("{}: {}", dbus_error.name, dbus_error.message);

    return 1;
}