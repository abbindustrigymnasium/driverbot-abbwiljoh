<template>
  <v-app id="content">
    <v-toolbar app id="toolbar">
      <v-toolbar-title class="headline text-uppercase">
        <span>Williams</span>
        <span class="font-weight-light">Bil</span>
      </v-toolbar-title>

      <v-spacer></v-spacer>
      <v-btn color="primary" dark @click.stop="dialog = true">Anslutningsalternativ</v-btn>
      <v-btn target="_blank" @click="Switch=!Switch">
        <span v-if="Switch!==true" class="mr-2">Buttons 1</span>
        <span v-else class="mr-2">Buttons 2</span>
      </v-btn>
    </v-toolbar>

    <v-content>
      <v-row align="center" justify="center">
        <v-dialog v-model="dialog" max-width="290" height="290">
          <v-card>
            <v-card-title class="headline">Anslutning till Server</v-card-title>

            <v-card-text style="height: 300px;">
              <v-text-field v-model="name" label="Name" filled></v-text-field>

              <v-text-field v-model="password" label="MQTT Password" filled></v-text-field>

              <v-text-field v-model="port" label="Port" filled></v-text-field>
              <v-text-field v-model="adress" label="Adress" filled></v-text-field>
            </v-card-text>

            <v-card-actions>
              <v-spacer></v-spacer>

              <v-btn color="green darken-1" text @click="save()">Spara</v-btn>
            </v-card-actions>
          </v-card>
        </v-dialog>
                                  <!-- En liten flik där man kan lägga till egna credentials -->
        <div>
          <Logger />

          <Buttons v-if="Switch" />
          <Buttons2 v-else />
        </div>
      </v-row>
    </v-content>
  </v-app>
</template>

<script>
import Buttons2 from "./components/Buttonsv2";
import Buttons from "./components/Buttons";
import Logger from "./components/Logger";

export default {
  name: "App",
  components: {
    Buttons,
    Buttons2,
    Logger
  },
  data() {
    return {
      Switch: false,
      dialog: false,
      name: "",       //Information för fliken
      password: "",
      port: "",
      adress: ""
    };
  },
  created() {
    let User = this.$store.getters.GetUser;   //MQTT-Credentials för hemsidan från store.js
    this.name = User.name;
    this.password = User.password;
    this.port = User.port;
    this.adress = User.adress;
  },

  methods: {
    save() {
      let User = {
        name: this.name,
        password: this.password,
        port: this.port,
        adress: this.adress
      };

      this.$store.dispatch("Save", User);   //Sparar användaren

      this.dialog = false;
    }
  },
  computed: {}
};
</script>
<style scoped>
.img {
  width: 40%;
  height: 40%;
  margin: auto;
  padding: 10px;
}
#logger {
  /* position: fixed;
  bottom: 0;
  right: 0; */
  width: 300px;
  height: 300px;
  border: black dotted 2px;

  word-wrap: break-word;
}

/* https://beautifuldingbats.com/pattern-generator/ https://css-tricks.com/using-svg/ */
/* Gradient beackgrounds: https://cssgradient.io  Väldigt snygga gradient*/ 
#toolbar {
  /* background-image:url("data:image/svg+xml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB3aWR0aD0iMTAwJSIgaGVpZ2h0PSIxMDAlIj48ZGVmcz48cGF0dGVybiBpZD0icGF0dGVybiIgd2lkdGg9IjEwMCIgaGVpZ2h0PSIxMDAiIHZpZXdCb3g9IjAgMCA0MCA0MCIgcGF0dGVyblVuaXRzPSJ1c2VyU3BhY2VPblVzZSIgcGF0dGVyblRyYW5zZm9ybT0icm90YXRlKDM2MCkiPjxyZWN0IGlkPSJwYXR0ZXJuLWJhY2tncm91bmQiIHg9IjAiIHk9IjAiIHdpZHRoPSI0MDAlIiBoZWlnaHQ9IjQwMCUiIGZpbGw9InRyYW5zcGFyZW50Ii8+ICA8IS0tLS0+IDwhLS0tLT4gPHBhdGggZD0ibSAwIDEwIGggNDAiIHN0cm9rZS13aWR0aD0iMjAiIHN0cm9rZT0iI2ZmZTA2NiIgc2hhcGUtcmVuZGVyaW5nPSJhdXRvIiBzdHJva2UtbGluZWNhcD0iYnV0dCIgc3Ryb2tlLWxpbmVqb2luPSJyb3VuZCIgZmlsbD0idHJhbnNwYXJlbnQiLz4gICAgPCEtLS0tPiA8IS0tLS0+IDxwYXRoIGQ9Im0wLDAgTDQwLDQwIiBzdHJva2Utd2lkdGg9IjIwIiBzdHJva2U9IiNmZjZiNmIiIHNoYXBlLXJlbmRlcmluZz0iYXV0byIgc3Ryb2tlLWxpbmVjYXA9InNxdWFyZSIgc3Ryb2tlLWxpbmVqb2luPSJyb3VuZCIgZmlsbD0idHJhbnNwYXJlbnQiLz48cGF0aCBkPSJtNDAsMCBMODAsNDAiIHN0cm9rZS13aWR0aD0iMjAiIHN0cm9rZT0iI2ZmNmI2YiIgc2hhcGUtcmVuZGVyaW5nPSJhdXRvIiBzdHJva2UtbGluZWNhcD0ic3F1YXJlIiBzdHJva2UtbGluZWpvaW49InJvdW5kIiBmaWxsPSJ0cmFuc3BhcmVudCIvPjxwYXRoIGQ9Im0tNDAsMCBMMCw0MCIgc3Ryb2tlLXdpZHRoPSIyMCIgc3Ryb2tlPSIjZmY2YjZiIiBzaGFwZS1yZW5kZXJpbmc9ImF1dG8iIHN0cm9rZS1saW5lY2FwPSJzcXVhcmUiIHN0cm9rZS1saW5lam9pbj0icm91bmQiIGZpbGw9InRyYW5zcGFyZW50Ii8+ICAgPC9wYXR0ZXJuPjwvZGVmcz4gPHJlY3QgZmlsbD0idXJsKCNwYXR0ZXJuKSIgaGVpZ2h0PSIxMDAlIiB3aWR0aD0iMTAwJSIgeT0iMCIgeD0iMCIvPjwvc3ZnPg==")
  } */
background-image: linear-gradient(90deg, rgba(124,16,16,0.8158613787311799) 0%, rgba(224,246,35,0.9587185215883228) 52%, rgba(27,255,4,0.5553571770505077) 100%);
}
#content {
/* background-image:url("data:image/svg+xml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB3aWR0aD0iMTAwJSIgaGVpZ2h0PSIxMDAlIj48ZGVmcz48cGF0dGVybiBpZD0icGF0dGVybiIgd2lkdGg9IjM1IiBoZWlnaHQ9IjM1IiB2aWV3Qm94PSIwIDAgNDAgNDAiIHBhdHRlcm5Vbml0cz0idXNlclNwYWNlT25Vc2UiIHBhdHRlcm5UcmFuc2Zvcm09InJvdGF0ZSgxODApIj48cmVjdCBpZD0icGF0dGVybi1iYWNrZ3JvdW5kIiB4PSIwIiB5PSIwIiB3aWR0aD0iNDAwJSIgaGVpZ2h0PSI0MDAlIiBmaWxsPSIjZmZmNGU2Ii8+ICA8IS0tLS0+IDwhLS0tLT4gPHBhdGggZD0iTTAgMjBhMjAgMjAgMCAxMTQwIDAiIHN0cm9rZS13aWR0aD0iMSIgc3Ryb2tlPSIjMWM3ZWQ2IiBzaGFwZS1yZW5kZXJpbmc9ImF1dG8iIHN0cm9rZS1saW5lY2FwPSJidXR0IiBzdHJva2UtbGluZWpvaW49InJvdW5kIiBmaWxsPSJ0cmFuc3BhcmVudCIvPiAgICA8IS0tLS0+IDwhLS0tLT4gPHBhdGggZD0iTTAgMjBjMTAgMCAyMCA4IDIwIDIwIDAtMTAgOC0yMCAyMC0yMCIgc3Ryb2tlLXdpZHRoPSIzIiBzdHJva2U9IiNmZmE4YTgiIHNoYXBlLXJlbmRlcmluZz0iYXV0byIgc3Ryb2tlLWxpbmVjYXA9ImJ1dHQiIHN0cm9rZS1saW5lam9pbj0icm91bmQiIGZpbGw9InRyYW5zcGFyZW50Ii8+ICAgIDwhLS0tLT4gPCEtLS0tPiA8cGF0aCBkPSJNMCA2MGEyMCAyMCAwIDExNDAgMCIgc3Ryb2tlLXdpZHRoPSIxIiBzdHJva2U9IiMxYzdlZDYiIHNoYXBlLXJlbmRlcmluZz0iYXV0byIgc3Ryb2tlLWxpbmVjYXA9ImJ1dHQiIHN0cm9rZS1saW5lam9pbj0icm91bmQiIGZpbGw9InRyYW5zcGFyZW50Ii8+ICAgPC9wYXR0ZXJuPjwvZGVmcz4gPHJlY3QgZmlsbD0idXJsKCNwYXR0ZXJuKSIgaGVpZ2h0PSIxMDAlIiB3aWR0aD0iMTAwJSIgeT0iMCIgeD0iMCIvPjwvc3ZnPg=="); */
background: linear-gradient(90deg, rgba(0,0,0,1) 0%, rgba(255,255,255,1) 52%, rgba(0,0,0,1) 100%);
}
</style>
