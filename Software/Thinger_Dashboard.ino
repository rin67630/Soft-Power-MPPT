/*
This is just a convenience file containing the JSON parameters to configure the example dashboard at thinger.io.
To use it first replace using the Find...
Replace using the facility of the Arduino IDE, 
- all occurances of "Device_replace_me" by the HOST_NAME of your device.
- all occurances of "User_replace_me" by your THINGER_USERNAME.

Then create an empty dashboard at thinger.io, open it, activate the configuration (the green slider at the top right),
click at the top left on "settings" and within the pop-up window on "developer", replace the code there by the code below
starting from the currently brace ( do not copy this comment).

Enjoy your dashboard, and modify it ad libitum.

 {
 "description": "SoftPowerMeter",
  "name": "SoftPower Efficiency Meter",
  "properties": {
    "columns": 4,
    "show_template": true
  },
  "tabs": [
    {
      "icon": "fas fa-tachometer-alt",
      "name": "Solar Swiss Army Knife",
      "widgets": [
        {
          "data": {
            "device": {
              "id": "Device_replace_me",
              "interval": 2,
              "mapping": "current",
              "resource": "energy",
              "update": "interval",
              "user": "User_replace_me"
            },
            "source": "device"
          },
          "layout": {
            "col": 2,
            "row": 15,
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
            "unit": "A Battery",
            "unit_size": "20px",
            "weight": "font-thin"
          },
          "type": "text"
        },
        {
          "data": {
            "device": {
              "id": "Device_replace_me",
              "interval": 2,
              "mapping": "current",
              "resource": "energy",
              "update": "events",
              "user": "User_replace_me"
            },
            "source": "device"
          },
          "layout": {
            "col": 2,
            "row": 0,
            "sizeX": 1,
            "sizeY": 6
          },
          "panel": {
            "color": "#e8cdfe"
          },
          "properties": {
            "majorTicks": 1,
            "max": 3,
            "min": -1,
            "plateColor": "#ffffff",
            "showValue": true,
            "textColor": "#1E313E",
            "tickColor": "#000000",
            "unit": "A Battery"
          },
          "type": "tachometer"
        },
        {
          "data": {
            "device": {
              "id": "Device_replace_me",
              "interval": 2,
              "mapping": "power",
              "resource": "energy",
              "update": "events",
              "user": "User_replace_me"
            },
            "source": "device"
          },
          "layout": {
            "col": 3,
            "row": 0,
            "sizeX": 1,
            "sizeY": 6
          },
          "panel": {
            "color": "#fed3ef"
          },
          "properties": {
            "majorTicks": 5,
            "max": 46,
            "min": -5,
            "plateColor": "#ffffff",
            "showValue": true,
            "textColor": "#1E313E",
            "tickColor": "#000000",
            "unit": "Power"
          },
          "type": "tachometer"
        },
        {
          "data": {
            "device_property": {
              "device": "SoftPowerMeter",
              "mapping": "pressure",
              "property": "persistance",
              "user": "User_replace_me"
            },
            "source": "device_property"
          },
          "layout": {
            "col": 3,
            "row": 6,
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
              "device": "SoftPowerMeter",
              "mapping": "temperature",
              "property": "persistance",
              "user": "User_replace_me"
            },
            "source": "device_property"
          },
          "layout": {
            "col": 2,
            "row": 6,
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
              "device": "SoftPowerMeter",
              "mapping": "summary",
              "property": "persistance",
              "user": "User_replace_me"
            },
            "source": "device_property"
          },
          "layout": {
            "col": 3,
            "row": 12,
            "sizeX": 1,
            "sizeY": 3
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
              "device": "SoftPowerMeter",
              "mapping": "wind",
              "property": "persistance",
              "user": "User_replace_me"
            },
            "source": "device_property"
          },
          "layout": {
            "col": 2,
            "row": 12,
            "sizeX": 1,
            "sizeY": 3
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
              "id": "Device_replace_me",
              "resource": "DC_out2",
              "user": "User_replace_me"
            },
            "source": "device"
          },
          "layout": {
            "col": 1,
            "row": 10,
            "sizeX": 1,
            "sizeY": 3
          },
          "panel": {
            "color": "#f5f9b7",
            "title": ""
          },
          "properties": {
            "icon": "fa-power-off",
            "iconColor": "#ffffff",
            "iconSize": 25,
            "offColor": "#888888",
            "onColor": "#00bb00",
            "style": "button"
          },
          "type": "boolean"
        },
        {
          "data": {
            "device": {
              "id": "Device_replace_me",
              "resource": "relay2",
              "user": "User_replace_me"
            },
            "source": "device"
          },
          "layout": {
            "col": 1,
            "row": 13,
            "sizeX": 1,
            "sizeY": 2
          },
          "panel": {
            "color": "#bbbbbb",
            "title": "Relay 2"
          },
          "properties": {
            "style": "switch"
          },
          "type": "boolean"
        },
        {
          "data": {
            "device": {
              "id": "Device_replace_me",
              "resource": "relay1",
              "user": "User_replace_me"
            },
            "source": "device"
          },
          "layout": {
            "col": 0,
            "row": 13,
            "sizeX": 1,
            "sizeY": 2
          },
          "panel": {
            "color": "#bbbbbb",
            "title": "Relay 1"
          },
          "properties": {
            "style": "switch"
          },
          "type": "boolean"
        },
        {
          "data": {
            "device": {
              "id": "Device_replace_me",
              "resource": "DC_out1",
              "user": "User_replace_me"
            },
            "source": "device"
          },
          "layout": {
            "col": 0,
            "row": 10,
            "sizeX": 1,
            "sizeY": 3
          },
          "panel": {
            "color": "#b7f9f7",
            "title": ""
          },
          "properties": {
            "icon": "fa-power-off",
            "iconColor": "#ffffff",
            "iconSize": 25,
            "offColor": "#888888",
            "onColor": "#00bb00",
            "style": "button"
          },
          "type": "boolean"
        },
        {
          "data": {
            "device": {
              "id": "Device_replace_me",
              "interval": 2,
              "mapping": "panel",
              "resource": "energy",
              "update": "events",
              "user": "User_replace_me"
            },
            "source": "device"
          },
          "layout": {
            "col": 0,
            "row": 0,
            "sizeX": 1,
            "sizeY": 6
          },
          "panel": {
            "color": "#b7f9f7"
          },
          "properties": {
            "majorTicks": 1,
            "max": 20,
            "min": 10,
            "plateColor": "#ffffff",
            "showValue": true,
            "textColor": "#1E313E",
            "tickColor": "#000000",
            "unit": "V Panel"
          },
          "type": "tachometer"
        },
        {
          "data": {
            "bucket": {
              "backend": "dynamodb",
              "id": "HOUR",
              "mapping": [
                "current",
                "voltage"
              ],
              "user": "User_replace_me"
            },
            "source": "bucket"
          },
          "layout": {
            "col": 0,
            "row": 26,
            "sizeX": 4,
            "sizeY": 9
          },
          "panel": {
            "color": "#ffffff"
          },
          "properties": {
            "axis": true,
            "color": {
              "current": "#026cee",
              "voltage": "#23d004"
            },
            "fill": true,
            "legend": true,
            "multiple_axes": true,
            "timespan": {
              "magnitude": "day",
              "mode": "relative",
              "period": "latest",
              "value": 2
            }
          },
          "type": "chart"
        },
        {
          "data": {
            "device": {
              "id": "Device_replace_me",
              "mapping": "int_resistance",
              "resource": "energy",
              "update": "events",
              "user": "User_replace_me"
            },
            "source": "device"
          },
          "layout": {
            "col": 3,
            "row": 15,
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
              "device": "SoftPowerMeter",
              "mapping": "Today",
              "property": "BAT",
              "user": "User_replace_me"
            },
            "source": "device_property"
          },
          "layout": {
            "col": 0,
            "row": 15,
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
              "device": "SoftPowerMeter",
              "mapping": "Yesterday",
              "property": "BAT",
              "user": "User_replace_me"
            },
            "source": "device_property"
          },
          "layout": {
            "col": 1,
            "row": 15,
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
              "id": "Device_replace_me",
              "interval": 2,
              "mapping": "voltage",
              "resource": "energy",
              "update": "interval",
              "user": "User_replace_me"
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
            "color": "#d6ffca"
          },
          "properties": {
            "majorTicks": 1,
            "max": 15,
            "min": 10,
            "plateColor": "#ffffff",
            "showValue": true,
            "textColor": "#1E313E",
            "tickColor": "#000000",
            "unit": "V Battery"
          },
          "type": "tachometer"
        },
        {
          "data": {
            "device": {
              "id": "Device_replace_me",
              "resource": "CV",
              "user": "User_replace_me"
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
            "color": "#b7f9f7"
          },
          "properties": {
            "max": 1024,
            "min": 0,
            "step": 10
          },
          "type": "slider"
        },
        {
          "data": {
            "device": {
              "id": "Device_replace_me",
              "resource": "CC",
              "user": "User_replace_me"
            },
            "source": "device"
          },
          "layout": {
            "col": 1,
            "row": 6,
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
              "id": "Device_replace_me",
              "interval": 5,
              "mapping": "CV",
              "resource": "energy",
              "update": "events",
              "user": "User_replace_me"
            },
            "source": "device"
          },
          "layout": {
            "col": 0,
            "row": 8,
            "sizeX": 1,
            "sizeY": 2
          },
          "panel": {
            "color": "#b7f9f7"
          },
          "properties": {
            "color": "#1E313E",
            "decimal_places": 0,
            "icon": "",
            "max": 1024,
            "min": 0,
            "size": "40px",
            "step": 10,
            "unit_size": "20px",
            "weight": "font-thin"
          },
          "type": "text"
        },
        {
          "data": {
            "device": {
              "id": "Device_replace_me",
              "interval": 5,
              "mapping": "CC",
              "resource": "energy",
              "update": "events",
              "user": "User_replace_me"
            },
            "source": "device"
          },
          "layout": {
            "col": 1,
            "row": 8,
            "sizeX": 1,
            "sizeY": 2
          },
          "panel": {
            "color": "#f5f9b7"
          },
          "properties": {
            "color": "#1E313E",
            "decimal_places": 0,
            "icon": "",
            "max": 1024,
            "min": 0,
            "size": "40px",
            "step": 10,
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
                "current",
                "voltage"
              ],
              "user": "User_replace_me"
            },
            "source": "bucket"
          },
          "layout": {
            "col": 0,
            "row": 17,
            "sizeX": 4,
            "sizeY": 9
          },
          "panel": {
            "color": "#ffffff"
          },
          "properties": {
            "axis": true,
            "color": {
              "current": "#2e90d1",
              "voltage": "#2de151"
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
        }
      ]
    }
  ]
}
 */
