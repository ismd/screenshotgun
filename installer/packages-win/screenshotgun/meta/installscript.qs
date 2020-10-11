function Component()
{
}

Component.prototype.createOperations = function()
{
    component.createOperations();

    if (systemInfo.productType === "windows") {
        component.addOperation("CreateShortcut", "@TargetDir@/screenshotgun.exe", "@StartMenuDir@/screenshotgun.lnk",
            "workingDirectory=@TargetDir@", "iconPath=@TargetDir@/screenshotgun.ico");
    }
}
