const acceptOnlyNumbers = (str) => {
    const pattern = /^\d+$/;
    return pattern.test(str);
};

export {acceptOnlyNumbers};