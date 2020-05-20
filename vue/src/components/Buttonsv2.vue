<template>
  <v-container id="box">
 <span id="hide">    {{Disconnect}}</span>
    <v-card class="elevation-12" color="grey lighten-1">
      <v-layout row>
        <v-flex class="justify-center mb-6">
          <v-btn class="ma-2" v-if="connected" tile color="red" icon @click="speed=850">
            85
            <v-icon>directions_car</v-icon>
          </v-btn>

          <v-btn
            class="ma-2 rotate-45"
            tile
            large
            color="teal"
            icon
            :disabled="!connected"
            @click="Send('direction','l45'); SubscribeLog('direction');"
          >
            <v-icon>keyboard_arrow_left</v-icon>
          </v-btn>
          <v-btn
            class="ma-2"
            tile
            large
            color="teal"
            icon
            :disabled="!connected"
            @click="Send('direction','f'+speed); SubscribeLog('direction');"
          >
            <v-icon>keyboard_arrow_up</v-icon>
          </v-btn>
          <v-btn
            class="ma-2 rotate-135"
            tile
            large
            color="teal"
            icon
            :disabled="!connected"
            @click="Send('direction','r45'); SubscribeLog('direction');"
          >
            <v-icon>keyboard_arrow_left</v-icon>
          </v-btn>

          <v-btn class="ma-2" tile v-if="connected" color="blue" icon @click="speed=900">
            90
            <v-icon>directions_car</v-icon>
          </v-btn>
        </v-flex>
      </v-layout>
      <v-layout row>
        <v-flex md6>
          <v-btn
            class="ma-2"
            tile
            large
            color="teal"
            icon
            :disabled="!connected"
            @click="Send('direction','l90'); SubscribeLog('direction');"
          >
            <v-icon>keyboard_arrow_left</v-icon>
          </v-btn>
        </v-flex>
        <v-flex md6>
          <v-btn v-if="!connected" class="ma-2" tile large :color="car" icon @click="Connect()">
            <v-icon>directions_car</v-icon>
          </v-btn>
          <v-btn v-else class="ma-2" tile large :color="car" icon @click="Send('direction','f0'); SubscribeLog('direction');">
            <v-icon>pause</v-icon>
          </v-btn>
        </v-flex>
        <v-flex md6>
          <v-btn
            class="ma-2"
            tile
            large
            color="teal"
            icon
            :disabled="!connected"
            @click="Send('direction','r90'); SubscribeLog('direction');"
          >
            <v-icon>keyboard_arrow_right</v-icon>
          </v-btn>
        </v-flex>
      </v-layout>
      <v-layout row>
        <v-flex class="justify-center mb-6">
          <v-btn class="ma-2" v-if="connected" tile color="green" icon @click="speed=950">
            95
            <v-icon>directions_car</v-icon>
          </v-btn>
          <v-btn
            class="ma-2 rotate-45"
            tile
            large
            color="teal"
            icon
            :disabled="!connected"
            @click="Send('direction','l135'); SubscribeLog('direction');"
          >
            <v-icon>keyboard_arrow_down</v-icon>
          </v-btn>
          <v-btn
            class="ma-2"
            tile
            large
            color="teal"
            icon
            :disabled="!connected"
            @click="Send('direction','b'+speed); SubscribeLog('direction');"
          >
            <v-icon>keyboard_arrow_down</v-icon>
          </v-btn>
          <v-btn
            class="ma-2 rotate-135"
            tile
            large
            color="teal"
            icon
            :disabled="!connected"
            @click="Send('direction','r135'); SubscribeLog('direction');"
          >
            <v-icon>keyboard_arrow_up</v-icon>
          </v-btn>

          <v-btn class="ma-2" tile v-if="connected" color="purple" icon @click="speed=1000">
            99
            <v-icon>directions_car</v-icon>
          </v-btn>
        </v-flex>
      </v-layout>
    </v-card>
  </v-container>
</template>

<script>
//Bibliotek som ska användas
var mqtt = require("mqtt");
export default {
  name: "Buttons",
  props: {
    //Data som skickas in i komponenten
  },

  data() {
    //All data som ska finnas i komponenten
    return {
      connected: false,
      car: "green",
      clientId: "notyetAssigned",
      client: null,
      options: {},
      speed: 500
    };
  },
  created() {
    //När komponenten är skapad
  },
  mounted() {
    //När komponenten är mountad (inladdad)
  },
  computed: {
    Disconnect() {
      if (this.$store.getters.connected == false) {
        // this.Send('direction','f0')
        return true;
      }
      return false;
    }
  },
  watch: {
    Disconnect: {
      handler: function(newVal) {
        if (newVal == true) {
          this.connected = false;
          this.client = mqtt.disconnect;
          this.car = "green";
        }
      }
    }
  },
  methods: {
    //Metoder
    Connect() {
      let ref = this;
      if (this.connected == true) {
        return "";
      }

      let User = this.$store.getters.GetUser;
      this.clientId =
        "WilliamBilKontroll" +
        Math.random()
          .toString(16)
          .substr(2, 8);
      var mqtt_url = "maqiatto.com";
      var url = "mqtt://" + mqtt_url;
      var options = {
        port: User.port,
        clientId: this.clientId,
        username: User.name,
        password: User.password
      };

      this.options = options;
      // console.log("connecting");
      this.client = mqtt.connect(url, options);
      // console.log("connected?");

      this.connected = true;
      this.client
        .on("connect", function() {
          // console.log("success");
          ref.Connecting(true);
        })
        .on("error", function() {
          // console.log("error");
          ref.Connecting(false);
        })
        .on("close", function() {
          ref.Connecting(false);
          // console.log("closing");
        });

      this.$store.dispatch("Connect", this.connected);

      if (this.connected == false) {
        this.car = "red";
      } else {
        this.car = "blue";
        this.Send('direction', this.clientId + " har anslutits.");
      }
    },

    Connecting(connected) {
      this.connected = connected;
      this.$store.dispatch("Connect", connected);
      // console.log(this.connected)
      if (connected == false) {
        this.car = "red";
      } else {
        this.car = "blue";
        this.Send('direction', this.clientId + " har anslutits.");
      }
    },

    Send(adress, message) {
      // console.log(message);
      this.client.publish(
        this.options.username + "/" + adress, //Exempel         "william.johansson@abbindustrigymnasium.se"+"/" + "direction",
        message
      );

      // this.$store.dispatch("addToLogger",'Bil: '+message);
    },

    SubscribeLog(adress) {
        this.client.subscribe(this.options.username+'/'+adress, {qos: 1})
        this.client.on('message', (topic, message)=> {
          this.$store.dispatch("addToLogger", message)
        })
      }

  }
};
</script>

<!-- CSS -->
<style scoped>
.big {
  font-size: 25px;
}
#Cooltext {
  color: black;
  text-decoration: underline;
}
#box {
  width: 400px;
  height: 400px;
}
#logger {
  position: fixed;
  bottom: 0;
  right: 0;
  width: 300px;
  height: 300px;
  border: black dotted 2px;

  word-wrap: break-word;
}
#hide{
 display: none;
}
.rotate-45 {
  filter: progid:DXImageTransform.Microsoft.BasicImage(rotation=0.5);
  -webkit-transform: rotate(45deg);
  -moz-transform: rotate(45deg);
  -ms-transform: rotate(45deg);
  -o-transform: rotate(45deg);
  transform: rotate(45deg);
}
.rotate-135 {
  filter: progid:DXImageTransform.Microsoft.BasicImage(rotation=1.5);
  -webkit-transform: rotate(135deg);
  -moz-transform: rotate(135deg);
  -ms-transform: rotate(135deg);
  -o-transform: rotate(135deg);
  transform: rotate(135deg);
}
</style>
