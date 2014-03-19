/**
 *  This file is for developers only.
 *
 *  This tests are made for the javascript functions used in GA module.
 *  These tests verify if the return values are properly working.
 *
 *  Hopefully this can be added somewhere else once Drupal core has JavaScript
 *  unit testing integrated.
 */

// JavaScript debugging
var base_url = window.location.protocol + '//' + window.location.host; 
console.dir(Drupal);

console.group("Test 'isDownload':");
console.log("Check if '/node/8' url is a file download. Expected: false, Result: %s.", Drupal.googleanalytics.isDownload(base_url + '/node/8'));
console.log("Check if '/files/foo1.zip' url is a file download. Expected: true, Result: %s.", Drupal.googleanalytics.isDownload(base_url + '/files/foo1.zip'));
console.log("Check if '/files/foo2.ddd' url is a file download. Expected: false, Result: %s.", Drupal.googleanalytics.isDownload(base_url + '/files/foo2.ddd'));
console.groupEnd();

console.group("Test 'isInternal':");
console.log("Check if base_url + '/node/1#foo=bar' url is internal. Expected: true, Result: %s.", Drupal.googleanalytics.isInternal(base_url + '/node/1#foo=bar'));
console.log("Check if base_url + '/node/2' url is internal. Expected: true, Result: %s.", Drupal.googleanalytics.isInternal(base_url + '/node/2'));
console.log("Check if base_url + '/go/foo' url is internal. Expected: true, Result: %s.", Drupal.googleanalytics.isInternal(base_url + '/go/foo'));
console.log("Check if 'http://example.com/node/3' url is internal. Expected: false, Result: %s.", Drupal.googleanalytics.isInternal('http://example.com/node/3'));
console.groupEnd();

console.group("Test 'isInternalSpecial':");
console.log("Check if base_url + '/go/foo' url is internal special. Expected: true, Result: %s.", Drupal.googleanalytics.isInternalSpecial(base_url + '/go/foo'));
console.log("Check if base_url + '/node/1' url is internal special. Expected: false, Result: %s.", Drupal.googleanalytics.isInternalSpecial(base_url + '/node/1'));
console.groupEnd();

console.group("Test 'getPageUrl':");
console.log("Get absolute internal url from full qualified url. Expected: '/node/1', Result: '%s'.", Drupal.googleanalytics.getPageUrl(base_url + '/node/1'));
console.log("Get absolute internal url from absolute url. Expected: '/node/1', Result: '%s'.", Drupal.googleanalytics.getPageUrl('/node/1'));
console.log("Get full qualified external url. Expected: 'http://example.com/node/2', Result: '%s'.", Drupal.googleanalytics.getPageUrl('http://example.com/node/2'));
console.groupEnd();

console.group("Test 'getDownloadExtension':");
console.log("Get extension of download filename. Expected: 'zip', Result: '%s'.", Drupal.googleanalytics.getDownloadExtension(base_url + '/files/foo1.zip'));
console.log("Get empty extension if not a download extension. Expected: '', Result: '%s'.", Drupal.googleanalytics.getDownloadExtension(base_url + '/files/foo2.dddd'));
console.groupEnd();

// List of top-level domains: example.com, example.net
console.group("Test 'isCrossDomain' (requires cross domain configuration):");
console.dir(Drupal.settings.google_analytics.trackCrossDomains);
console.log("Check if url is in cross domain list. Expected: true, Result: %s.", Drupal.googleanalytics.isCrossDomain('example.com', Drupal.settings.google_analytics.trackCrossDomains));
console.log("Check if url is in cross domain list. Expected: true, Result: %s.", Drupal.googleanalytics.isCrossDomain('example.net', Drupal.settings.google_analytics.trackCrossDomains));
console.log("Check if url is in cross domain list. Expected: false, Result: %s.", Drupal.googleanalytics.isCrossDomain('www.example.com', Drupal.settings.google_analytics.trackCrossDomains));
console.log("Check if url is in cross domain list. Expected: false, Result: %s.", Drupal.googleanalytics.isCrossDomain('www.example.net', Drupal.settings.google_analytics.trackCrossDomains));
console.groupEnd();

