.. _caf_ble_bond:

CAF: Bluetooth LE bond module
#############################

.. contents::
   :local:
   :depth: 2

The |ble_bond| of the :ref:`lib_caf` (CAF) allows to introduce Bluetooth LE bonding to the application.
The module also allows to delete bonds for the default Bluetooth local identity.

Configuration
*************

Before using the module make sure that the following Kconfig options are enabled:

* :kconfig:`CONFIG_BT_BONDABLE`
* :kconfig:`CONFIG_BT_SETTINGS`
* :kconfig:`CONFIG_CAF_SETTINGS_LOADER`
* :kconfig:`CONFIG_CAF_BLE_COMMON_EVENTS`

The device must be Bluetooth bondable and bonds must be stored in the non-volatile memory (settings).
The :ref:`caf_settings_loader` is used to load content of the settings area during boot.

The |ble_bond| is enabled using :kconfig:`CONFIG_CAF_BLE_BOND`.
This Kconfig option selects :kconfig:`CONFIG_CAF_BLE_BOND_SUPPORTED` option to indicate that the |ble_bond| is implemented in the application.

Enabling bond erase
===================

The |ble_bond| can erase bonds for the default Bluetooth local identity when a predefined button click is detected.
The module subscribes for :c:struct:`click_event` to detect the button clicks.

Complete the following steps to enable bond erase:

1. Set the :kconfig:`CONFIG_CAF_BLE_BOND_PEER_ERASE_CLICK` to enable the bond erase when a predefined button click is detected.
#. Set :kconfig:`CONFIG_CAF_BLE_BOND_PEER_ERASE_CLICK_KEY_ID` to define the key ID of the button used to erase bonds.
#. Select one of the following Kconfig options to specify the click type (:c:enum:`click`) that triggers the bond erase:

   * :kconfig:`CONFIG_CAF_BLE_BOND_PEER_ERASE_CLICK_SHORT` - :c:enumerator:`CLICK_SHORT`,
   * :kconfig:`CONFIG_CAF_BLE_BOND_PEER_ERASE_CLICK_LONG` - :c:enumerator:`CLICK_LONG`,
   * :kconfig:`CONFIG_CAF_BLE_BOND_PEER_ERASE_CLICK_DOUBLE` - :c:enumerator:`CLICK_DOUBLE`.

#. By default, detection of the specific click for a specific button always triggers the bond erase.
   Set :kconfig:`CONFIG_CAF_BLE_BOND_PEER_ERASE_CLICK_TIMEOUT` to specify the waiting time for detecting the button click after boot.
   The timeout is specified in milliseconds.
   The button click is ignored if it occurrs after the timeout.

Implementation details
**********************

The |ble_bond| can be used as a default implementation of Bluetooth LE bond functionality for simple applications.
The module does not broadcast information about performed Bluetooth LE peer operations using :c:struct:`ble_peer_operation_event`.
The module assumes that only default Bluetooth local identity is used.

.. note::
   If your application requires an application-specific Bluetooth LE bond and peer management, you must provide your own implementation of the Bluetooth LE bond module.
   See :ref:`nrf_desktop_ble_bond` for an example of implementation.

.. |ble_bond| replace:: Bluetooth LE bond module
