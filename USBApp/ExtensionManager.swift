//
//  ExtensionDelegate.swift
//  USBApp
//
//  Created by Scott Knight on 6/13/19.
//  Copyright © 2019 Scott Knight. All rights reserved.
//

import Foundation
import SystemExtensions
import os.log

class ExtensionManager : NSObject, OSSystemExtensionRequestDelegate {
    
    static let shared = ExtensionManager()
    
    func activate() {
        let activationRequest = OSSystemExtensionRequest.activationRequest(forExtensionWithIdentifier: "sc.knight.MyUserUSBInterfaceDriver", queue: .main)
        activationRequest.delegate = self
        OSSystemExtensionManager.shared.submitRequest(activationRequest)
    }
    
    func deactivate() {
        // This doesn't seem to work in b1 not sure why
        let activationRequest = OSSystemExtensionRequest.deactivationRequest(forExtensionWithIdentifier: "sc.knight.MyUserUSBInterfaceDriver", queue: .main)
        activationRequest.delegate = self
        OSSystemExtensionManager.shared.submitRequest(activationRequest)
    }
    
    func request(_ request: OSSystemExtensionRequest, actionForReplacingExtension existing: OSSystemExtensionProperties, withExtension ext: OSSystemExtensionProperties) -> OSSystemExtensionRequest.ReplacementAction {
        os_log("sysex actionForReplacingExtension %@ %@", existing, ext)
        
        return .replace
    }
    
    func requestNeedsUserApproval(_ request: OSSystemExtensionRequest) {
        os_log("sysex needsUserApproval")
        
    }
    
    func request(_ request: OSSystemExtensionRequest, didFinishWithResult result: OSSystemExtensionRequest.Result) {
        os_log("sysex didFinishWithResult %@", result.rawValue)
        
    }
    
    func request(_ request: OSSystemExtensionRequest, didFailWithError error: Error) {
        os_log("sysex didFailWithError %@", error.localizedDescription)
    }
}
