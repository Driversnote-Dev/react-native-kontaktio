/**
 * @providesModule Kontakt
 * @flow
 */
'use strict';

var NativeKontakt = require('NativeModules').Kontakt;

/**
 * High-level docs for the Kontakt iOS API can be written here.
 */

var Kontakt = {
  test: function() {
    NativeKontakt.test();
  }
};

module.exports = Kontakt;
