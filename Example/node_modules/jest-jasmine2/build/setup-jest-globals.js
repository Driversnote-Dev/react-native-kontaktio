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



require('jest-matchers');const getState = _require.getState,setState = _require.setState;var _require2 =
require('jest-snapshot');const initializeSnapshotState = _require2.initializeSnapshotState,addPlugins = _require2.addPlugins;

// Get suppressed errors form  jest-matchers that weren't throw during
// test execution and add them to the test result, potentially failing
// a passing test.
const addSuppressedErrors = result => {var _getState =
  getState();const suppressedErrors = _getState.suppressedErrors;
  setState({ suppressedErrors: [] });
  if (suppressedErrors.length) {
    result.status = 'failed';

    result.failedExpectations = suppressedErrors.map(error => ({
      actual: '',
      expected: '',
      message: error.message,
      passed: false,
      stack: error.stack }));

  }
};

const patchJasmine = () => {
  global.jasmine.Spec = (realSpec => {
    const Spec = function Spec(attr) {
      const resultCallback = attr.resultCallback;
      attr.resultCallback = function (result) {
        addSuppressedErrors(result);
        resultCallback.call(attr, result);
      };

      const onStart = attr.onStart;
      attr.onStart = context => {
        setState({ currentTestName: context.getFullName() });
        onStart && onStart.call(attr, context);
      };

      realSpec.call(this, attr);
    };

    Spec.prototype = realSpec.prototype;
    for (const statics in realSpec) {
      if (Object.prototype.hasOwnProperty.call(realSpec, statics)) {
        Spec[statics] = realSpec[statics];
      }
    }
    return Spec;

  })(global.jasmine.Spec);
};






module.exports = (_ref) => {let testPath = _ref.testPath,config = _ref.config;
  addPlugins(config.snapshotSerializers);
  setState({ testPath });
  patchJasmine();
  const snapshotState = initializeSnapshotState(
  testPath,
  config.updateSnapshot,
  '',
  config.expand);

  setState({ snapshotState });
  // Return it back to the outer scope (test runner outside the VM).
  return snapshotState;
};