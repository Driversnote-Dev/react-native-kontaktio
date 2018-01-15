/**
 * Copyright (c) 2014-present, Facebook, Inc. All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 *
 * 
 */
'use strict';




const diff = require('jest-diff');
const fileExists = require('jest-file-exists');
const fs = require('fs');
const path = require('path');
const SnapshotState = require('./State');var _require =
require('./plugins');const getPlugins = _require.getPlugins,addPlugins = _require.addPlugins;var _require2 =






require('jest-matcher-utils');const EXPECTED_COLOR = _require2.EXPECTED_COLOR,ensureNoExpected = _require2.ensureNoExpected,matcherHint = _require2.matcherHint,RECEIVED_COLOR = _require2.RECEIVED_COLOR;var _require3 =
require('./utils');const SNAPSHOT_EXTENSION = _require3.SNAPSHOT_EXTENSION;

const cleanup = (hasteFS, update) => {
  const pattern = '\\.' + SNAPSHOT_EXTENSION + '$';
  const files = hasteFS.matchFiles(pattern);
  const filesRemoved = files.
  filter(snapshotFile => !fileExists(
  path.resolve(
  path.dirname(snapshotFile),
  '..',
  path.basename(snapshotFile, '.' + SNAPSHOT_EXTENSION)),

  hasteFS)).

  map(snapshotFile => {
    if (update) {
      fs.unlinkSync(snapshotFile);
    }
  }).
  length;

  return {
    filesRemoved };

};

let snapshotState;

const initializeSnapshotState = (
testFile,
update,
testPath,
expand) =>
new SnapshotState(testFile, update, testPath, expand);

const getSnapshotState = () => snapshotState;

const toMatchSnapshot = function (received, expected) {
  this.dontThrow();const

  currentTestName = this.currentTestName,isNot = this.isNot,snapshotState = this.snapshotState;

  if (isNot) {
    throw new Error(
    'Jest: `.not` cannot be used with `.toMatchSnapshot()`.');

  }

  ensureNoExpected(expected, '.toMatchSnapshot');

  if (!snapshotState) {
    throw new Error('Jest: snapshot state must be initialized.');
  }

  const result = snapshotState.match(currentTestName, received);const
  pass = result.pass;

  if (pass) {
    return { message: '', pass: true };
  } else {const
    count = result.count,expected = result.expected,actual = result.actual;


    const expectedString = expected.trim();
    const actualString = actual.trim();
    const diffMessage = diff(
    expectedString,
    actualString,
    {
      aAnnotation: 'Snapshot',
      bAnnotation: 'Received',
      expand: snapshotState.expand });



    const message =
    () => matcherHint('.toMatchSnapshot', 'value', '') + '\n\n' +
    `${ RECEIVED_COLOR('Received value') } does not match ` +
    `${ EXPECTED_COLOR('stored snapshot ' + count) }.\n\n` + (
    diffMessage ||
    RECEIVED_COLOR('- ' + expectedString) + '\n' +
    EXPECTED_COLOR('+ ' + actualString));


    return { message, pass: false };
  }
};

const toThrowErrorMatchingSnapshot = function (received, expected) {
  this.dontThrow();const
  isNot = this.isNot;

  if (isNot) {
    throw new Error(
    'Jest: `.not` cannot be used with `.toThrowErrorMatchingSnapshot()`.');

  }

  ensureNoExpected(expected, '.toThrowErrorMatchingSnapshot');

  let error;

  try {
    received();
  } catch (e) {
    error = e;
  }

  if (error === undefined) {
    throw new Error(
    matcherHint('.toThrowErrorMatchingSnapshot', '() => {}', '') + '\n\n' +
    `Expected the function to throw an error.\n` +
    `But it didn't throw anything.`);

  }

  return toMatchSnapshot.call(this, error.message);
};

module.exports = {
  EXTENSION: SNAPSHOT_EXTENSION,
  SnapshotState,
  addPlugins,
  cleanup,
  getPlugins,
  getSnapshotState,
  initializeSnapshotState,
  toMatchSnapshot,
  toThrowErrorMatchingSnapshot };