TAKEOWN /F C:\Users\%username%\Desktop\payload2\WindowsTrustedRTProxy.sys
icacls C:\Users\%username%\Desktop\payload2\WindowsTrustedRTProxy.sys /inheritance:d
icacls C:\Users\%username%\Desktop\payload2\WindowsTrustedRTProxy.sys /grant:r %username%:RX
icacls C:\Users\%username%\Desktop\payload2\WindowsTrustedRTProxy.sys /grant:r system:RX
icacls C:\Users\%username%\Desktop\payload2\WindowsTrustedRTProxy.sys /grant:r administrators:RX
icacls C:\Users\%username%\Desktop\payload2\WindowsTrustedRTProxy.sys /grant:r "ALL APPLICATION PACKAGES":RX