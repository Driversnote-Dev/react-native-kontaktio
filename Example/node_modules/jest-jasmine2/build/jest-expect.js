/**
 * Copyright (c) 2014-present, Facebook, Inc. All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 *
 * 
 */
'use strict';var _require =




require('jest-matchers');const expect = _require.expect,setState = _require.setState;var _require2 =




require('jest-snapshot');const toMatchSnapshot = _require2.toMatchSnapshot,toThrowErrorMatchingSnapshot = _require2.toThrowErrorMatchingSnapshot;








module.exports = config => {
  global.expect = expect;
  setState({
    expand: config.expand });

  expect.extend({ toMatchSnapshot, toThrowErrorMatchingSnapshot });

  const jasmine = global.jasmine;
  jasmine.addMatchers = jasmineMatchersObject => {
    const jestMatchersObject = Object.create(null);
    Object.keys(jasmineMatchersObject).forEach(name => {
      jestMatchersObject[name] = function () {
        const result = jasmineMatchersObject[name](jasmine.matchersUtil, null);
        // if there is no 'negativeCompare', both should be handled by `compare`
        const negativeCompare = result.negativeCompare || result.compare;

        return this.isNot ?
        negativeCompare.apply(null, arguments) :
        result.compare.apply(null, arguments);
      };
    });

    global.expect.extend(jestMatchersObject);
  };
};