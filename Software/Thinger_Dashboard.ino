/*
This is just a convenience file containing the JSON parameters to configure the example dashboard at thinger.io.
if you are not using the default username and device name, you must replace (e.g.using the Find/Replace facility of the Arduino IDE):
- all occurances of "Soft-Power" by the HOST_NAME of your device.
- all occurances of "SoftPower1" by your THINGER_USERNAME.

Then create an empty dashboard at thinger.io, open it, activate the configuration (the green slider at the top right),
click at the top left on "settings" and within the pop-up window on "developer", replace the code there by the code below
**starting from the next line until the last line** ( do not copy the last line):

{
  "description": "Soft-Power 1xINA226, 2x D-SUN",
  "name": "Soft-Power",
  "properties": {
    "columns": 4,
    "show_template": true
  },
  "tabs": [
    {
      "icon": "fas fa-tachometer-alt",
      "name": "Soft Power",
      "widgets": [
        {
          "data": {
            "device": {
              "id": "Soft-Power",
              "interval": 2,
              "mapping": "Iaux",
              "resource": "measure",
              "update": "events",
              "user": "SoftPower1"
            },
            "source": "device"
          },
          "layout": {
            "col": 3,
            "row": 12,
            "sizeX": 1,
            "sizeY": 6
          },
          "panel": {
            "color": "#f5f9b7"
          },
          "properties": {
            "majorTicks": 1,
            "max": 3,
            "min": -1,
            "plateColor": "#ffffff",
            "showValue": true,
            "textColor": "#1E313E",
            "tickColor": "#000000",
            "unit": "A Aux"
          },
          "type": "tachometer"
        },
        {
          "data": {
            "device": {
              "id": "Soft-Power",
              "interval": 2,
              "mapping": "Waux",
              "resource": "measure",
              "update": "interval",
              "user": "SoftPower1"
            },
            "source": "device"
          },
          "layout": {
            "col": 3,
            "row": 18,
            "sizeX": 1,
            "sizeY": 6
          },
          "panel": {
            "color": "#f5f9b7"
          },
          "properties": {
            "majorTicks": 1,
            "max": 10,
            "min": 0,
            "plateColor": "#ffffff",
            "showValue": true,
            "textColor": "#1E313E",
            "tickColor": "#000000",
            "unit": "W Aux"
          },
          "type": "tachometer"
        },
        {
          "data": {
            "device_property": {
              "device": "Soft-Power",
              "mapping": "pressure",
              "property": "persistance",
              "user": "SoftPower1"
            },
            "source": "device_property"
          },
          "layout": {
            "col": 0,
            "row": 18,
            "sizeX": 1,
            "sizeY": 6
          },
          "panel": {
            "color": "#dddddd"
          },
          "properties": {
            "majorTicks": 100,
            "max": 1100,
            "min": 900,
            "plateColor": "#ffffff",
            "showValue": true,
            "textColor": "#1E313E",
            "tickColor": "#000000",
            "unit": "hPa"
          },
          "type": "tachometer"
        },
        {
          "data": {
            "device_property": {
              "device": "Soft-Power",
              "mapping": "temperature",
              "property": "persistance",
              "user": "SoftPower1"
            },
            "source": "device_property"
          },
          "layout": {
            "col": 0,
            "row": 12,
            "sizeX": 1,
            "sizeY": 6
          },
          "panel": {
            "color": "#dddddd"
          },
          "properties": {
            "majorTicks": 10,
            "max": 40,
            "min": -10,
            "plateColor": "#ffffff",
            "showValue": true,
            "textColor": "#1E313E",
            "tickColor": "#000000",
            "unit": "°C Outside"
          },
          "type": "tachometer"
        },
        {
          "data": {
            "device_property": {
              "device": "Soft-Power",
              "mapping": "summary",
              "property": "persistance",
              "user": "SoftPower1"
            },
            "source": "device_property"
          },
          "layout": {
            "col": 0,
            "row": 24,
            "sizeX": 1,
            "sizeY": 5
          },
          "panel": {
            "color": "#dddddd",
            "title": "Weather"
          },
          "properties": {
            "color": "#1E313E",
            "decimal_places": 0,
            "icon": "",
            "size": "40px",
            "unit": "",
            "unit_size": "20px",
            "weight": "font-thin"
          },
          "type": "text"
        },
        {
          "data": {
            "device_property": {
              "device": "Soft-Power",
              "mapping": "wind",
              "property": "persistance",
              "user": "SoftPower1"
            },
            "source": "device_property"
          },
          "layout": {
            "col": 0,
            "row": 29,
            "sizeX": 1,
            "sizeY": 5
          },
          "panel": {
            "color": "#dddddd",
            "title": "Wind"
          },
          "properties": {
            "color": "#1E313E",
            "decimal_places": 1,
            "icon": "",
            "size": "50px",
            "unit": "m/s",
            "unit_size": "20px",
            "weight": "font-thin"
          },
          "type": "text"
        },
        {
          "data": {
            "device": {
              "id": "Soft-Power",
              "resource": "DC_out2",
              "user": "SoftPower1"
            },
            "source": "device"
          },
          "layout": {
            "col": 3,
            "row": 4,
            "sizeX": 1,
            "sizeY": 2
          },
          "panel": {
            "color": "#f5f9b7",
            "title": "On/Off"
          },
          "properties": {
            "icon": "fa-power-off",
            "iconColor": "#ffffff",
            "iconSize": 25,
            "offColor": "#888888",
            "onColor": "#00bb00",
            "style": "switch"
          },
          "type": "boolean"
        },
        {
          "data": {
            "device": {
              "id": "Soft-Power",
              "resource": "relay2",
              "user": "SoftPower1"
            },
            "source": "device"
          },
          "layout": {
            "col": 0,
            "row": 3,
            "sizeX": 1,
            "sizeY": 3
          },
          "panel": {
            "color": "#bbbbbb",
            "title": "Relay 2"
          },
          "properties": {
            "icon": "fa-power-off",
            "iconColor": "#ffffff",
            "iconSize": "",
            "offColor": "#6a6762",
            "onColor": "#00bb00",
            "style": "button"
          },
          "type": "boolean"
        },
        {
          "data": {
            "device": {
              "id": "Soft-Power",
              "resource": "relay1",
              "user": "SoftPower1"
            },
            "source": "device"
          },
          "layout": {
            "col": 0,
            "row": 0,
            "sizeX": 1,
            "sizeY": 3
          },
          "panel": {
            "color": "#bbbbbb",
            "title": "Relay 1"
          },
          "properties": {
            "icon": "fa-power-off",
            "iconColor": "#ffffff",
            "iconSize": "",
            "offColor": "#686664",
            "onColor": "#00bb00",
            "style": "button"
          },
          "type": "boolean"
        },
        {
          "data": {
            "device": {
              "id": "Soft-Power",
              "resource": "DC_out1",
              "user": "SoftPower1"
            },
            "source": "device"
          },
          "layout": {
            "col": 2,
            "row": 4,
            "sizeX": 1,
            "sizeY": 2
          },
          "panel": {
            "color": "#b7f9f7",
            "title": "High Power"
          },
          "properties": {
            "icon": "fa-power-off",
            "iconColor": "#ffffff",
            "iconSize": 25,
            "max": 100,
            "min": 0,
            "offColor": "#888888",
            "onColor": "#00bb00",
            "step": 1,
            "style": "switch"
          },
          "type": "boolean"
        },
        {
          "data": {
            "device": {
              "id": "Soft-Power",
              "interval": 2,
              "mapping": "Vpan",
              "resource": "measure",
              "update": "interval",
              "user": "SoftPower1"
            },
            "source": "device"
          },
          "layout": {
            "col": 1,
            "row": 6,
            "sizeX": 1,
            "sizeY": 6
          },
          "panel": {
            "color": "#d6ffca"
          },
          "properties": {
            "majorTicks": 1,
            "max": 24,
            "min": 10,
            "plateColor": "#ffffff",
            "showValue": true,
            "textColor": "#1E313E",
            "tickColor": "#000000",
            "unit": "V Pan"
          },
          "type": "tachometer"
        },
        {
          "data": {
            "device": {
              "id": "Soft-Power",
              "mapping": "ohm",
              "resource": "measure",
              "update": "events",
              "user": "SoftPower1"
            },
            "source": "device"
          },
          "layout": {
            "col": 0,
            "row": 6,
            "sizeX": 1,
            "sizeY": 2
          },
          "panel": {
            "color": "#ffffff"
          },
          "properties": {
            "color": "#1E313E",
            "decimal_places": 3,
            "gradient": true,
            "icon": "",
            "majorTicks": 1,
            "max": 1,
            "min": -1,
            "plateColor": "#ffffff",
            "showValue": true,
            "size": "50px",
            "textColor": "#1E313E",
            "tickColor": "#000000",
            "unit": "Ω",
            "unit_size": "20px",
            "weight": "font-thin"
          },
          "type": "text"
        },
        {
          "data": {
            "device_property": {
              "device": "Soft-Power",
              "mapping": "Today",
              "property": "BAT",
              "user": "SoftPower1"
            },
            "source": "device_property"
          },
          "layout": {
            "col": 0,
            "row": 10,
            "sizeX": 1,
            "sizeY": 2
          },
          "panel": {
            "color": "#ffffff"
          },
          "properties": {
            "color": "#1E313E",
            "decimal_places": 2,
            "gradient": true,
            "icon": "",
            "majorTicks": 1,
            "max": 1,
            "min": -1,
            "plateColor": "#ffffff",
            "showValue": true,
            "size": "50px",
            "textColor": "#1E313E",
            "tickColor": "#000000",
            "unit": "Ah Today",
            "unit_size": "20px",
            "weight": "font-thin"
          },
          "type": "text"
        },
        {
          "data": {
            "device_property": {
              "device": "Soft-Power",
              "mapping": "Yesterday",
              "property": "BAT",
              "user": "SoftPower1"
            },
            "source": "device_property"
          },
          "layout": {
            "col": 0,
            "row": 8,
            "sizeX": 1,
            "sizeY": 2
          },
          "panel": {
            "color": "#ffffff"
          },
          "properties": {
            "color": "#1E313E",
            "decimal_places": 2,
            "gradient": true,
            "icon": "",
            "majorTicks": 1,
            "max": 1,
            "min": -1,
            "plateColor": "#ffffff",
            "showValue": true,
            "size": "50px",
            "textColor": "#1E313E",
            "tickColor": "#000000",
            "unit": "Ah  d-1",
            "unit_size": "20px",
            "weight": "font-thin"
          },
          "type": "text"
        },
        {
          "data": {
            "device": {
              "id": "Soft-Power",
              "interval": 2,
              "mapping": "Vaux",
              "resource": "measure",
              "update": "interval",
              "user": "SoftPower1"
            },
            "source": "device"
          },
          "layout": {
            "col": 3,
            "row": 6,
            "sizeX": 1,
            "sizeY": 6
          },
          "panel": {
            "color": "#f5f9b7"
          },
          "properties": {
            "majorTicks": 1,
            "max": 9,
            "min": 0,
            "plateColor": "#ffffff",
            "showValue": true,
            "textColor": "#1E313E",
            "tickColor": "#000000",
            "unit": "V Aux"
          },
          "type": "tachometer"
        },
        {
          "data": {
            "device": {
              "id": "Soft-Power",
              "resource": "scc",
              "user": "SoftPower1"
            },
            "source": "device"
          },
          "layout": {
            "col": 2,
            "row": 2,
            "sizeX": 1,
            "sizeY": 2
          },
          "panel": {
            "color": "#b7f9f7"
          },
          "properties": {
            "max": 0,
            "min": 1024,
            "step": 10
          },
          "type": "slider"
        },
        {
          "data": {
            "device": {
              "id": "Soft-Power",
              "resource": "aux",
              "user": "SoftPower1"
            },
            "source": "device"
          },
          "layout": {
            "col": 3,
            "row": 2,
            "sizeX": 1,
            "sizeY": 2
          },
          "panel": {
            "color": "#f5f9b7"
          },
          "properties": {
            "max": 0,
            "min": 1024,
            "step": 10
          },
          "type": "slider"
        },
        {
          "data": {
            "device": {
              "id": "Soft-Power",
              "interval": 5,
              "mapping": "scc_mvolt",
              "resource": "control",
              "update": "interval",
              "user": "SoftPower1"
            },
            "source": "device"
          },
          "layout": {
            "col": 2,
            "row": 0,
            "sizeX": 1,
            "sizeY": 2
          },
          "panel": {
            "color": "#b7f9f7",
            "title": "Bat Setpoint"
          },
          "properties": {
            "color": "#1E313E",
            "decimal_places": 0,
            "icon": "",
            "max": 1024,
            "min": 0,
            "size": "40px",
            "step": 10,
            "unit": "mV",
            "unit_size": "20px",
            "weight": "font-thin"
          },
          "type": "text"
        },
        {
          "data": {
            "device": {
              "id": "Soft-Power",
              "interval": 5,
              "mapping": "aux_mvolt",
              "resource": "control",
              "update": "interval",
              "user": "SoftPower1"
            },
            "source": "device"
          },
          "layout": {
            "col": 3,
            "row": 0,
            "sizeX": 1,
            "sizeY": 2
          },
          "panel": {
            "color": "#f5f9b7",
            "title": "Aux Setpoint"
          },
          "properties": {
            "color": "#1E313E",
            "decimal_places": 0,
            "icon": "",
            "max": 1024,
            "min": 0,
            "size": "40px",
            "step": 10,
            "unit": "mV",
            "unit_size": "20px",
            "weight": "font-thin"
          },
          "type": "text"
        },
        {
          "data": {
            "bucket": {
              "backend": "dynamodb",
              "id": "MIN",
              "mapping": [
                "Ibat",
                "Vbat"
              ],
              "user": "SoftPower1"
            },
            "source": "bucket"
          },
          "layout": {
            "col": 1,
            "row": 24,
            "sizeX": 3,
            "sizeY": 10
          },
          "panel": {
            "color": "#b7f9f7"
          },
          "properties": {
            "axis": true,
            "color": {
              "Ibat": "#0155f1",
              "Vbat": "#1eda03"
            },
            "fill": true,
            "legend": true,
            "multiple_axes": true,
            "timespan": {
              "magnitude": "hour",
              "mode": "relative",
              "period": "latest",
              "value": 8
            }
          },
          "type": "chart"
        },
        {
          "data": {
            "device": {
              "id": "Soft-Power",
              "interval": 2,
              "mapping": "Vbat",
              "resource": "measure",
              "update": "interval",
              "user": "SoftPower1"
            },
            "source": "device"
          },
          "layout": {
            "col": 2,
            "row": 6,
            "sizeX": 1,
            "sizeY": 6
          },
          "panel": {
            "color": "#b7f9f7"
          },
          "properties": {
            "majorTicks": 1,
            "max": 15,
            "min": 10,
            "plateColor": "#ffffff",
            "showValue": true,
            "textColor": "#1E313E",
            "tickColor": "#000000",
            "unit": "V Bat"
          },
          "type": "tachometer"
        },
        {
          "data": {
            "device": {
              "id": "Soft-Power",
              "interval": 2,
              "mapping": "Ibat",
              "resource": "measure",
              "update": "interval",
              "user": "SoftPower1"
            },
            "source": "device"
          },
          "layout": {
            "col": 2,
            "row": 12,
            "sizeX": 1,
            "sizeY": 6
          },
          "panel": {
            "color": "#b7f9f7"
          },
          "properties": {
            "majorTicks": 1,
            "max": 3,
            "min": -1,
            "plateColor": "#ffffff",
            "showValue": true,
            "textColor": "#1E313E",
            "tickColor": "#000000",
            "unit": "A Bat"
          },
          "type": "tachometer"
        },
        {
          "data": {
            "device": {
              "id": "Soft-Power",
              "interval": 2,
              "mapping": "Wpan",
              "resource": "measure",
              "update": "interval",
              "user": "SoftPower1"
            },
            "source": "device"
          },
          "layout": {
            "col": 1,
            "row": 18,
            "sizeX": 1,
            "sizeY": 6
          },
          "panel": {
            "color": "#d6ffca",
            "colors": []
          },
          "properties": {
            "majorTicks": 5,
            "max": 46,
            "min": -5,
            "plateColor": "#ffffff",
            "showValue": true,
            "textColor": "#1E313E",
            "tickColor": "#000000",
            "unit": "W Pan"
          },
          "type": "tachometer"
        },
        {
          "data": {
            "device": {
              "id": "Soft-Power",
              "interval": 2,
              "mapping": "Ipan",
              "resource": "measure",
              "update": "interval",
              "user": "SoftPower1"
            },
            "source": "device"
          },
          "layout": {
            "col": 1,
            "row": 12,
            "sizeX": 1,
            "sizeY": 6
          },
          "panel": {
            "color": "#d6ffca"
          },
          "properties": {
            "majorTicks": 1,
            "max": 3,
            "min": -1,
            "plateColor": "#ffffff",
            "showValue": true,
            "textColor": "#1E313E",
            "tickColor": "#000000",
            "unit": "A Pan"
          },
          "type": "tachometer"
        },
        {
          "data": {
            "device": {
              "id": "Soft-Power",
              "interval": 2,
              "mapping": "Wbat",
              "resource": "measure",
              "update": "interval",
              "user": "SoftPower1"
            },
            "source": "device"
          },
          "layout": {
            "col": 2,
            "row": 18,
            "sizeX": 1,
            "sizeY": 6
          },
          "panel": {
            "color": "#b7f9f7"
          },
          "properties": {
            "majorTicks": 5,
            "max": 46,
            "min": -5,
            "plateColor": "#ffffff",
            "showValue": true,
            "textColor": "#1E313E",
            "tickColor": "#000000",
            "unit": "W Bat"
          },
          "type": "tachometer"
        },
        {
          "data": {
            "device": {
              "id": "Soft-Power",
              "interval": 5,
              "mapping": "efficiency",
              "resource": "measure",
              "update": "interval",
              "user": "SoftPower1"
            },
            "source": "device"
          },
          "layout": {
            "col": 1,
            "row": 0,
            "sizeX": 1,
            "sizeY": 6
          },
          "panel": {
            "color": "#e8cdfe"
          },
          "properties": {
            "majorTicks": 10,
            "max": 100,
            "min": -50,
            "plateColor": "#ffffff",
            "showValue": true,
            "textColor": "#1E313E",
            "tickColor": "#000000",
            "unit": "% Efficiency"
          },
          "type": "tachometer"
        }
      ]
    }
  ]
}
 */
